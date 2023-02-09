/* 
 * File:   timer2.c
 * Author: Walid Omar
 *
 * Created on February 9, 2023, 1:19 PM
 */

#include"timer2.h"
static void(*TMR2_InterruptHandler)(void) = NULL;
uint8 t2_preload_value = 0;
Std_ReturnType Timer2_Init(const timer2_t *t2_obj){
    Std_ReturnType ret_value =E_NOT_OK;
    if(NULL==t2_obj)
    {
        ret_value =E_NOT_OK;
    }
    else
    {
        TIMER2_DISABLE();
        TIMER2_PRESCALER_CONFIG(t2_obj->prescaler);
        TIMER2_POSTSCALER_CONFIG(t2_obj->postscaler);
        TMR2 = t2_obj->proload_value;
        t2_preload_value = TMR2;
#if TMR2_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
        TMR2_INTERRUPT_ENABLE();
        TMR2_INTERRUPT_CLEAR_FLAG();
        TMR2_InterruptHandler=t2_obj->timer2_ExceptionHandler;
#if INTERRUPT_FEATURE == INTERRUPT_PRIORITY_ENABLE
        if(HIGH_PRIORITY == t2_obj->priority)
        {
            GLOBAL_INTE_HIGH_ENABLE();  
            TMR3_INTERRUPT_HIGH_PRIORITY();
        }
        else if(LOW_PRIORITY == t2_obj->priority)
        {
            GLOBAL_INTE_LOW_ENABLE();
            TMR3_INTERRUPT_LOW_PRIORITY();
        }
        else{/* Nothing */}
#else
        GLOBAL_INTERRUPT_ENABLE();
        PERIPHERAL_INTERRUPT_ENABLE();
#endif
#endif    
        
        TIMER2_ENABLE();
         ret_value =E_OK;
    }
    return ret_value;
}
Std_ReturnType Timer2_DeInit(const timer2_t *t2_obj){
    Std_ReturnType ret_value =E_NOT_OK;
    if(NULL==t2_obj)
    {
        ret_value =E_NOT_OK;
    }
    else
    {
#if TMR2_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
        TMR2_INTERRUPT_DISABLE();
#endif
        TIMER2_DISABLE();
         ret_value =E_OK;
    }
    return ret_value;
}
Std_ReturnType Timer2_Write(const timer2_t *t2_obj, uint8 value){
    Std_ReturnType ret_value =E_NOT_OK;
    if(NULL==t2_obj)
    {
        ret_value =E_NOT_OK;
    }
    else
    {
         TMR2=value;
         ret_value =E_OK;
    }
    return ret_value;
}
Std_ReturnType Timer2_Read(const timer2_t *t2_obj, uint8 *value){
    Std_ReturnType ret_value =E_NOT_OK;
    if((NULL==t2_obj) || (NULL==value))
    {
        ret_value =E_NOT_OK;
    }
    else
    {
        *value=TMR2;
         ret_value =E_OK;
    }
    return ret_value;
}

void TMR2_ISR(void)
{
    TMR2_INTERRUPT_CLEAR_FLAG();
    TMR2=t2_preload_value;
    if(TMR2_InterruptHandler)
    {
        TMR2_InterruptHandler();
    }
}