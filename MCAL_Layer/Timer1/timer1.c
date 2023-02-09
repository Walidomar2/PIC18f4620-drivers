/* 
 * File:   timer1.c
 * Author: Walid Omar
 *
 * Created on February 6, 2023, 11:16 AM
 */

#include "timer1.h"

static inline void Timer1_Mode(const timer1_t *t_object);
static inline void Register_Format_Select(const timer1_t *t_object);
static inline void Timer1_EXT_OSC_Config(const timer1_t *t_object);
static volatile void(*TMR1_InterruptHandler)(void) = NULL;

static volatile uint16 preload_value = 0;

Std_ReturnType Timer1_Init(const timer1_t *t1_object){
    Std_ReturnType ret_value = E_NOT_OK;
    if(NULL == t1_object)
    {
        ret_value = E_NOT_OK;
    }
    else
    {
        TIMER1_DISABLE();
        TIMER1_PRESCALER_CONFIG(t1_object->prescaler);
        Timer1_Mode(t1_object);
        TMR1H = (t1_object->preload_value) >> 8;
        TMR1L = (uint8)(t1_object->preload_value);
        preload_value = t1_object->preload_value;
        
#if TMR1_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE 
        TMR1_INTERRUPT_ENABLE();
        TMR1_INTERRUPT_CLEAR_FLAG();
        TMR1_InterruptHandler = t1_object->timer1_ExceptionHandler;
        
#if INTERRUPT_FEATURE == INTERRUPT_PRIORITY_ENABLE
        INTERRUPT_PRIORITY_ENABLE();
        if(HIGH_PRIORITY == t1_object->priority)
        {
            GLOBAL_INTE_HIGH_ENABLE();  
            TMR1_INTERRUPT_HIGH_PRIORITY();
        }
        else if(LOW_PRIORITY == t1_object->priority)
        {
            GLOBAL_INTE_LOW_ENABLE();
            TMR1_INTERRUPT_LOW_PRIORITY();
        }
        else{/* Nothing */}
#else
        GLOBAL_INTERRUPT_ENABLE();
        PERIPHERAL_INTERRUPT_ENABLE();
#endif
#endif
        TIMER1_ENABLE();
        ret_value = E_OK;
    }
    return ret_value;
}

Std_ReturnType Timer1_Deinit(const timer1_t *t1_object){
    Std_ReturnType ret_value = E_NOT_OK;
    if(NULL == t1_object)
    {
        ret_value = E_NOT_OK;
    }
    else
    {
#if TMR1_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE 
        TMR1_INTERRUPT_DISABLE();
#endif
        TIMER1_DISABLE();
        ret_value = E_OK;
    }
    return ret_value;
}

Std_ReturnType Timer1_Write(const timer1_t *t1_object ,uint16 value){
    Std_ReturnType ret_value = E_NOT_OK;
    if( NULL == t1_object)
    {
        ret_value = E_NOT_OK;
    }
    else
    {
        TMR1H = (value) >> 8;
        TMR1L = (uint8)(value);
        ret_value = E_OK;
    }
    return ret_value;
}

Std_ReturnType Timer1_Read(const timer1_t *t1_object ,uint16 *value){
    Std_ReturnType ret_value = E_NOT_OK;
    uint8 L_Timer1 =0,H_Timer1=0;
    
    if((NULL == t1_object) || (NULL == value))
    {
        ret_value = E_NOT_OK;
    }
    else
    {
        L_Timer1=TMR1L;
        H_Timer1=TMR1H;
        *value=(uint16)((H_Timer1 << 8) + L_Timer1);
        ret_value = E_OK;
    }
    return ret_value;
}


/*----------------------------------- Helper Functions ---------------------------------------*/

static inline void Timer1_Mode(const timer1_t *t_object){
        if(TIMER1_TIMER_MODE == t_object->mode)
        {
            TIMER1_TIMER_MODE_ENABLE();
        }
        else if(TIMER1_COUNTER_MODE == t_object->mode)
        {
            TIMER1_COUNTER_MODE_ENABLE();
            if(TIMER1_SYNC_COUNTER == t_object->synchronization)            {TIMER1_SYNCH_COUNTER(); }
            else if(TIMER1_ASYNC_COUNTER == t_object->synchronization)      {TIMER1_ASYNCH_COUNTER(); }
            else{TIMER1_ASYNCH_COUNTER(); }
        }
        else
        {
            /* Nothing */
        }
}

static inline void Register_Format_Select(const timer1_t *t_object){
        if(t_object->format == TIMER1_8BIT_REG)
        {
            TIMER1_REG_8BIT_FORMAT(); 
        }
        else if(t_object->format == TIMER1_16BIT_REG)
        {
            TIMER1_REG_16BIT_FORMAT(); 
        }
        else
        {
            TIMER1_REG_8BIT_FORMAT();
        }
}

static inline void Timer1_EXT_OSC_Config(const timer1_t *t_object){
        if(TIMER1_EXT_OSC_ENABLE==t_object->ext_osc_config)             {TIMER1_OSC_ENABLE(); }
        else if(TIMER1_EXT_OSC_DISABLE==t_object->ext_osc_config)       {TIMER1_OSC_DISABLE(); }
        else{TIMER1_OSC_DISABLE(); }
}

void TMR1_ISR(void)
{
    TMR1_INTERRUPT_CLEAR_FLAG();
    TMR1H = (preload_value ) >> 8;
    TMR1L = (uint8)(preload_value) ;
    if(TMR1_InterruptHandler)
    {
        TMR1_InterruptHandler();
    }
}