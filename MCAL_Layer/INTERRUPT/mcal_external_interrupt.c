/* 
 * File:   mcal_external_interrupt.c
 * Author: Walid Omar
 *
 * Created on December 31, 2022, 9:23 PM
 */

#include "mcal_external_interrupt.h"
#include "mcal_interrupt_manager.h"
static Std_ReturnType INTx_Priority_Config(const interrupt_INTx_t *object);
static Std_ReturnType Edge_Config(const interrupt_INTx_t *object);
static Std_ReturnType RBx_Priority_Config(const interrupt_RBx_t *object);

static void(*INT0_InterruptHandler)(void) = NULL; // will store the address of the INT0 ISR in application layer 
static void(*INT1_InterruptHandler)(void) = NULL; // will store the address of the INT1 ISR in application layer 
static void(*INT2_InterruptHandler)(void) = NULL; // will store the address of the INT2 ISR in application layer 

static Std_ReturnType INT0_SetInterruptHandler(void(*InterruptHandler)(void)); // will set the address of the INT0 ISR in application to INT0_InterruptHandler
static Std_ReturnType INT1_SetInterruptHandler(void(*InterruptHandler)(void)); // will set the address of the INT1 ISR in application to INT0_InterruptHandler
static Std_ReturnType INT2_SetInterruptHandler(void(*InterruptHandler)(void)); // will set the address of the INT2 ISR in application to INT0_InterruptHandler

static void(*RB4_InterruptHandlerHigh)(void) = NULL; // will store the address of the RB4_HIGH VOLTAGE ISR in application layer 
static void(*RB4_InterruptHandlerLow)(void)  = NULL; // will store the address of the RB4_LOW VOLTAGE ISR in application layer 

static void(*RB5_InterruptHandlerHigh)(void) = NULL; // will store the address of the RB5_HIGH_VOLTAGE ISR in application layer 
static void(*RB5_InterruptHandlerLow)(void)  = NULL; // will store the address of the RB5_LOW_VOLTAGE ISR in application layer 

static void(*RB6_InterruptHandlerHigh)(void) = NULL; // will store the address of the RB6_HIGH_VOLTAGE ISR in application layer 
static void(*RB6_InterruptHandlerLow)(void)  = NULL; // will store the address of the RB6_LOW_VOLTAGE ISR in application layer 

static void(*RB7_InterruptHandlerHigh)(void) = NULL; // will store the address of the RB7_HIGH_VOLTAGE ISR in application layer 
static void(*RB7_InterruptHandlerLow)(void)  = NULL; // will store the address of the RB7_LOW_VOLTAGE ISR in application layer 


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
                    #if INTERRUPT_FEATURE==INTERRUPT_PRIORITY_ENABLE
                    GLOBAL_INTE_HIGH_ENABLE();
                    #else
                    GLOBAL_INTERRUPT_ENABLE();
                    PERIPHERAL_INTERRUPT_ENABLE();
                    #endif
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
        #else
        GLOBAL_INTERRUPT_ENABLE();
        PERIPHERAL_INTERRUPT_ENABLE();
        #endif
        switch(object->RBx_pin.Pin){
                case PIN4:
                    RB4_InterruptHandlerHigh = object->EXT_InterruptHandlerHigh;
                    RB4_InterruptHandlerLow  = object->EXT_InterruptHandlerLow;
                    break;
                case PIN5:
                    RB5_InterruptHandlerHigh = object->EXT_InterruptHandlerHigh;
                    RB5_InterruptHandlerLow  = object->EXT_InterruptHandlerLow;
                    break;
                case PIN6:
                    RB6_InterruptHandlerHigh = object->EXT_InterruptHandlerHigh;
                    RB6_InterruptHandlerLow  = object->EXT_InterruptHandlerLow;
                    break;
                case PIN7:
                    RB7_InterruptHandlerHigh = object->EXT_InterruptHandlerHigh;
                    RB7_InterruptHandlerLow  = object->EXT_InterruptHandlerLow;
                    break;
                default:
                    ret_value=E_NOT_OK;
        }    
        
        EXT_INTERRUPT_RBx_ENABLE();
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
        INTERRUPT_PRIORITY_ENABLE();
        switch(object->INTx_pin.Pin){
                case PIN1:
                   if(object->priority == LOW_PRIORITY)
                   { 
                       EXT_INTERRUPT_INT1_LOW_PRIORITY();
                       GLOBAL_INTE_LOW_ENABLE();
                   }     
                   else if(object->priority == HIGH_PRIORITY)
                   {
                       EXT_INTERRUPT_INT1_HIGH_PRIORITY();
                       GLOBAL_INTE_HIGH_ENABLE();  
                   }
                   else{ /* Nothing */}     
                    ret_value = E_OK;
                    break;
                case PIN2:
                    if(object->priority == LOW_PRIORITY) 
                    {  
                        EXT_INTERRUPT_INT2_LOW_PRIORITY();
                        GLOBAL_INTE_LOW_ENABLE();
                    }      
                    else if(object->priority == HIGH_PRIORITY)
                    { 
                        EXT_INTERRUPT_INT2_HIGH_PRIORITY();
                        GLOBAL_INTE_HIGH_ENABLE();
                    }
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
    INTERRUPT_PRIORITY_ENABLE();
    Std_ReturnType ret_value=E_NOT_OK;
    if(NULL == object)
    {
        ret_value=E_NOT_OK;
    }
    else
    {
        if(HIGH_PRIORITY == object->priority){ 
            EXT_INTERRUPT_RBx_HIGH_PRIORITY();
            GLOBAL_INTE_HIGH_ENABLE();
        }
        else if(LOW_PRIORITY == object->priority){ 
            EXT_INTERRUPT_RBx_LOW_PRIORITY();
            GLOBAL_INTE_LOW_ENABLE();
        }
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

void RB4_ISR(uint8 logic){
    EXT_INTERRUPT_RBx_CLEAR_FLAG();
   if(1 == logic){
    if(RB4_InterruptHandlerHigh)
    {
        RB4_InterruptHandlerHigh();
    }
  }
   else if(0 == logic)
   {
      if(RB4_InterruptHandlerLow)
    {
        RB4_InterruptHandlerLow();
    } 
   }
   else{ /*Nothing*/ }
}

void RB5_ISR(uint8 logic){
    EXT_INTERRUPT_RBx_CLEAR_FLAG();
   if(1 == logic){
    if(RB5_InterruptHandlerHigh)
    {
        RB5_InterruptHandlerHigh();
    }
  }
   else if(0 == logic)
   {
      if(RB5_InterruptHandlerLow)
    {
        RB5_InterruptHandlerLow();
    } 
   }
   else{ /*Nothing*/ }
}

void RB6_ISR(uint8 logic){
    EXT_INTERRUPT_RBx_CLEAR_FLAG();
    if(1 == logic){
    if(RB6_InterruptHandlerHigh)
    {
        RB6_InterruptHandlerHigh();
    }
  }
   else if(0 == logic)
   {
      if(RB6_InterruptHandlerLow)
    {
        RB6_InterruptHandlerLow();
    } 
   }
   else{ /*Nothing*/ }
}

void RB7_ISR(uint8 logic){
    EXT_INTERRUPT_RBx_CLEAR_FLAG();
    if(1 == logic){
    if(RB7_InterruptHandlerHigh)
    {
        RB7_InterruptHandlerHigh();
    }
  }
   else if(0 == logic)
   {
      if(RB7_InterruptHandlerLow)
    {
        RB7_InterruptHandlerLow();
    } 
   }
   else{ /*Nothing*/ }
}
