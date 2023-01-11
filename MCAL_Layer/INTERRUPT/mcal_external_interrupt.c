/* 
 * File:   mcal_external_interrupt.c
 * Author: Walid Omar
 *
 * Created on December 31, 2022, 9:23 PM
 */

#include "mcal_external_interrupt.h"
static Std_ReturnType INTx_Priority_Config(const interrupt_INTx_t *object);
static Std_ReturnType Edge_Config(const interrupt_INTx_t *object);
static Std_ReturnType RBx_Priority_Config(const interrupt_RBx_t *object);

static void(*INT0_InterruptHandler)(void) = NULL; // will store the address of the INT0 ISR in application layer 
static void(*INT1_InterruptHandler)(void) = NULL; // will store the address of the INT1 ISR in application layer 
static void(*INT2_InterruptHandler)(void) = NULL; // will store the address of the INT2 ISR in application layer 

static Std_ReturnType INT0_SetInterruptHandler(void(*InterruptHandler)(void)); // will set the address of the INT0 ISR in application to INT0_InterruptHandler
static Std_ReturnType INT1_SetInterruptHandler(void(*InterruptHandler)(void)); // will set the address of the INT1 ISR in application to INT0_InterruptHandler
static Std_ReturnType INT2_SetInterruptHandler(void(*InterruptHandler)(void)); // will set the address of the INT2 ISR in application to INT0_InterruptHandler


Std_ReturnType Interrupt_INTx_Enable(const interrupt_INTx_t *object){
    Std_ReturnType ret_value=E_NOT_OK;
    if(NULL == object){
        ret_value=E_NOT_OK;
        }
    else
    {
        ret_value = gpio_pin_init(&(object->INTx_pin));
        
        switch(object->INTx_pin.Pin){
                case PIN0 :
                    EXT_INTERRUPT_INT0_DISABLE();
                    EXT_INTERRUPT_INT0_CLEAR_FLAG(); 
                    Edge_Config(object);
                    INT0_SetInterruptHandler(object->EXT_InterruptHandler);
                    GLOBAL_INTERRUPT_ENABLE();
                    PERIPHERAL_INTERRUPT_ENABLE();
                    EXT_INTERRUPT_INT0_ENABLE();
                    ret_value = E_OK;
                    break;
                case PIN1 : 
                    EXT_INTERRUPT_INT1_DISABLE();
                    EXT_INTERRUPT_INT1_CLEAR_FLAG();
                    Edge_Config(object);
                    #if INTERRUPT_FEATURE==INTERRUPT_PRIORITY_ENABLE
                    INTx_Priority_Config(object);
                    #else 
                    GLOBAL_INTERRUPT_ENABLE();
                    PERIPHERAL_INTERRUPT_ENABLE();
                    #endif
                    INT1_SetInterruptHandler(object->EXT_InterruptHandler);
                    EXT_INTERRUPT_INT1_ENABLE();
                    ret_value = E_OK;
                    break;
                case PIN2 :
                    EXT_INTERRUPT_INT2_DISABLE();
                    EXT_INTERRUPT_INT2_CLEAR_FLAG();
                    Edge_Config(object);
                    #if INTERRUPT_FEATURE==INTERRUPT_PRIORITY_ENABLE
                    INTx_Priority_Config(object);
                    #else 
                    GLOBAL_INTERRUPT_ENABLE();
                    PERIPHERAL_INTERRUPT_ENABLE();
                    #endif
                    INT2_SetInterruptHandler(object->EXT_InterruptHandler);
                    EXT_INTERRUPT_INT2_ENABLE();
                    ret_value = E_OK;
                    break;
                default : ret_value = E_NOT_OK;
        }
    }
    return ret_value;
}

Std_ReturnType Interrupt_INTx_Disable(const interrupt_INTx_t *object){
    Std_ReturnType ret_value=E_NOT_OK;
    if(NULL == object){
        ret_value=E_NOT_OK;
        }
    else
    {
        switch(object->INTx_pin.Pin){
                case PIN0 :
                    EXT_INTERRUPT_INT0_DISABLE();
                    ret_value = E_OK;
                    break;
                case PIN1 : 
                    EXT_INTERRUPT_INT1_DISABLE();
                    ret_value = E_OK;
                    break;
                case PIN2 :
                    EXT_INTERRUPT_INT2_DISABLE();
                    ret_value = E_OK;
                    break;
                default : ret_value = E_NOT_OK;
        }
        
    }
    return ret_value;
}

Std_ReturnType Interrupt_RBx_Enable(const interrupt_RBx_t *object){
    Std_ReturnType ret_value=E_NOT_OK;
    if(NULL == object){
        ret_value=E_NOT_OK;
        }
    else
    {
        ret_value = gpio_pin_init(&(object->RBx_pin));
        EXT_INTERRUPT_RBx_DISABLE();
        EXT_INTERRUPT_RBx_CLEAR_FLAG();
        #if INTERRUPT_FEATURE==INTERRUPT_PRIORITY_ENABLE
        RBx_Priority_Config(object);
        #endif
        EXT_INTERRUPT_RBx_ENABLE();
        ret_value=E_OK;
    }
    return ret_value; 
}

Std_ReturnType Interrupt_RBx_Disable(const interrupt_RBx_t *object){
    Std_ReturnType ret_value=E_NOT_OK;
    if(NULL == object){
        ret_value=E_NOT_OK;
        }
    else
    {
        EXT_INTERRUPT_RBx_DISABLE();
        ret_value=E_OK;
    }
    return ret_value;
}


static Std_ReturnType Edge_Config(const interrupt_INTx_t *object){
    Std_ReturnType ret_value = E_NOT_OK;
    if(NULL == object)
    {
        ret_value = E_NOT_OK;
    }
    else
    {
        switch(object->INTx_pin.Pin){
                case PIN0:
                    if( object->edge == INTERRUPT_FALLING_EDGE )      { EXT_INTERRUPT_INT0_FALL_EDGE(); }
                    else if ( object->edge == INTERRUPT_RISING_EDGE ) { EXT_INTERRUPT_INT0_RISE_EDGE();}
                    else{/* Nothing */}
                    ret_value = E_OK;
                    break;
                case PIN1:
                    if(object->edge == INTERRUPT_FALLING_EDGE)         { EXT_INTERRUPT_INT1_FALL_EDGE(); }
                    else if (object->edge == INTERRUPT_RISING_EDGE)    { EXT_INTERRUPT_INT1_RISE_EDGE(); }
                    else{ /*Nothing*/ }
                    ret_value = E_OK;
                    break;
                case PIN2:
                    if(object->edge == INTERRUPT_FALLING_EDGE)         { EXT_INTERRUPT_INT2_FALL_EDGE(); }  
                    else if(object->edge == INTERRUPT_RISING_EDGE)     { EXT_INTERRUPT_INT2_RISE_EDGE(); }
                    else{ /*Nothing*/ }
                    ret_value = E_OK;
                    break;
                default : ret_value = E_NOT_OK;
        }
        
    }
    return ret_value;
}

#if INTERRUPT_FEATURE==INTERRUPT_PRIORITY_ENABLE

static Std_ReturnType INTx_Priority_Config(const interrupt_INTx_t *object){
    Std_ReturnType ret_value = E_NOT_OK;
    if(NULL == object)
    {
        ret_value = E_NOT_OK;
    }
    else
    { 
        switch(object->INTx_pin.Pin){
                case PIN1:
                   if(object->priority == LOW_PRIORITY)       { EXT_INTERRUPT_INT1_LOW_PRIORITY(); }     
                   else if(object->priority == HIGH_PRIORITY) { EXT_INTERRUPT_INT1_HIGH_PRIORITY();}
                   else{ /* Nothing */}     
                    ret_value = E_OK;
                    break;
                case PIN2:
                    if(object->priority == LOW_PRIORITY)      {  EXT_INTERRUPT_INT2_LOW_PRIORITY(); }      
                    else if(object->priority == HIGH_PRIORITY){  EXT_INTERRUPT_INT2_HIGH_PRIORITY();}
                    else{ /*Nothing*/ }    
                    ret_value = E_OK;
                    break;
                default : ret_value = E_NOT_OK;  
        }
    }
       return ret_value;
    
}

static Std_ReturnType RBx_Priority_Config(const interrupt_RBx_t *object)
{
    Std_ReturnType ret_value=E_NOT_OK;
    if(NULL == object)
    {
        ret_value=E_NOT_OK;
    }
    else
    {
        if(HIGH_PRIORITY == object->priority)      { EXT_INTERRUPT_RBx_HIGH_PRIORITY(); }
        else if(LOW_PRIORITY == object->priority)  { EXT_INTERRUPT_RBx_LOW_PRIORITY();  }
        else{ /*Nothing*/ }
         ret_value=E_OK;  
    }
    return ret_value;
    
}

#endif


static Std_ReturnType INT0_SetInterruptHandler(void(*InterruptHandler)(void)){
    Std_ReturnType ret_value=E_NOT_OK;
    if(NULL == InterruptHandler){
        ret_value = E_NOT_OK;
    }
    else{
        INT0_InterruptHandler = InterruptHandler ;
        ret_value = E_OK;
    }
    return ret_value;
}

static Std_ReturnType INT1_SetInterruptHandler(void(*InterruptHandler)(void)){
    Std_ReturnType ret_value=E_NOT_OK;
    if(NULL == InterruptHandler){
        ret_value = E_NOT_OK;
    }
    else{
        INT1_InterruptHandler = InterruptHandler ;
        ret_value = E_OK;
    }
    return ret_value;
}

static Std_ReturnType INT2_SetInterruptHandler(void(*InterruptHandler)(void)){
    Std_ReturnType ret_value=E_NOT_OK;
    if(NULL == InterruptHandler){
        ret_value = E_NOT_OK;
    }
    else{
        INT2_InterruptHandler = InterruptHandler ;
        ret_value = E_OK;
    }
    return ret_value;
}

void INT0_ISR(void){
    EXT_INTERRUPT_INT0_CLEAR_FLAG(); 
    
    if(INT0_InterruptHandler)
    {
        INT0_InterruptHandler();
    }
}

void INT1_ISR(void){
    EXT_INTERRUPT_INT1_CLEAR_FLAG(); 
    if(INT1_InterruptHandler)
    {
        INT1_InterruptHandler();
    }
}

void INT2_ISR(void){
    EXT_INTERRUPT_INT2_CLEAR_FLAG(); 
    
    if(INT2_InterruptHandler)
    {
        INT2_InterruptHandler();
    }
}

