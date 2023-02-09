/* 
 * File:   timer3.c
 * Author: Walid Omar
 *
 * Created on February 9, 2023, 2:20 PM
 */

#include "timer3.h"
static void(*TMR3_InterruptHandler)(void) = NULL;
static inline void Timer3_Mode_Config(const timer3_t *t3_obj);
static inline void Timer3_Format_Config(const timer3_t *t3_obj);
uint16 t3_preload_value;

Std_ReturnType Timer3_Init(const timer3_t *t3_obj){
    Std_ReturnType ret_value = E_NOT_OK;
    if(NULL == t3_obj)
    {
        ret_value = E_NOT_OK;
    }
    else
    {
        
        TIMER3_DISABLE();
        TIMER3_PRESCALER_CONFIG(t3_obj->prescaler);
        Timer3_Mode_Config(t3_obj);
        TMR3H=(t3_obj->preload_value) >> 8;
        TMR3L=(uint8)(t3_obj->preload_value);
        t3_preload_value=t3_obj->preload_value;
#if TMR3_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
        TMR3_INTERRUPT_ENABLE();
        TMR3_INTERRUPT_CLEAR_FLAG();
        TMR3_InterruptHandler = t3_obj->timer3_ExceptionHandler;
        
#if INTERRUPT_FEATURE == INTERRUPT_PRIORITY_ENABLE
        if(HIGH_PRIORITY == t3_obj->priority)
        {
            GLOBAL_INTE_HIGH_ENABLE();  
            TMR3_INTERRUPT_HIGH_PRIORITY();
        }
        else if(LOW_PRIORITY == t3_obj->priority)
        {
            GLOBAL_INTE_LOW_ENABLE();
            TMR3_INTERRUPT_LOW_PRIORITY()
        }
        else{/* Nothing */}
#else
        GLOBAL_INTERRUPT_ENABLE();
        PERIPHERAL_INTERRUPT_ENABLE();
#endif
#endif
        
        TIMER3_ENABLE();
        ret_value = E_OK;
    }
    return ret_value;
}

Std_ReturnType Timer3_Deinit(const timer3_t *t3_obj){
    Std_ReturnType ret_value = E_NOT_OK;
    if(NULL == t3_obj)
    {
        ret_value = E_NOT_OK;
    }
    else
    {
#if TMR3_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
        TMR3_INTERRUPT_DISABLE();
#endif
        TIMER3_DISABLE();
        
        ret_value = E_OK;
    }
    return ret_value;
}

Std_ReturnType Timer3_Write(const timer3_t *t3_obj ,uint16 value){
    Std_ReturnType ret_value = E_NOT_OK;
    if(NULL == t3_obj)
    {
        ret_value = E_NOT_OK;
    }
    else
    {
        TMR3H=(value) >> 8;
        TMR3L=(uint8)(value);
        t3_preload_value = value;
        
        ret_value = E_OK;
    }
    return ret_value;
}

Std_ReturnType Timer3_Read(const timer3_t *t3_obj ,uint16 *value){
    Std_ReturnType ret_value = E_NOT_OK;
    uint8 t3_L=0,t3_H=0;
    if(NULL == t3_obj)
    {
        ret_value = E_NOT_OK;
    }
    else
    {
       t3_L = TMR3L;
       t3_H = TMR3H;
       *value = (uint16)((t3_H << 8) + t3_L);
        ret_value = E_OK;
    }
    return ret_value;
}

/*----------------------------------- Helper Functions ---------------------------------*/
void TMR3_ISR(void){
    TMR3_INTERRUPT_CLEAR_FLAG();
    TMR3H=(t3_preload_value) >> 8;
    TMR3L=(uint8)(t3_preload_value);
    if(TMR3_InterruptHandler)
    {
        TMR3_InterruptHandler();
    }
}

static inline void Timer3_Mode_Config(const timer3_t *t3_obj)
{
    if(TIMER3_TIMER_MODE == t3_obj->mode)
    {
        TIMER3_TIMER_MODE_ENABLE();
    }
    else if(TIMER3_COUNTER_MODE == t3_obj->mode)
    {
        TIMER3_COUNTER_MODE_ENABLE();
        if(TIMER3_SYNC_COUNTER == t3_obj->synchronization)
        {
            TIMER3_SYNC_COUNTER_MODE();
        }
        else if(TIMER3_ASYNC_COUNTER == t3_obj->synchronization)
        {
            TIMER3_ASYNC_COUNTER_MODE();
        }
        else{/* Nothing*/}
    }
    else{/* Nothing */}
}

static inline void Timer3_Format_Config(const timer3_t *t3_obj){
    if(TIMER3_8BIT_REG == t3_obj->format)            {TIMER3_REG_8BIT_FORMAT();}
    else if(TIMER3_16BIT_REG == t3_obj->format)      {TIMER3_REG_16BIT_FORMAT();}
    else{/* Nothing */}
}