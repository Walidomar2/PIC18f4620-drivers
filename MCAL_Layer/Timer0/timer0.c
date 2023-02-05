/* 
 * File:   timer0.c
 * Author: Walid Omar
 *
 * Created on January 30, 2023, 3:47 PM
 */

#include "timer0.h"
static Std_ReturnType Prescaler_config(const timer0_t *object);
static Std_ReturnType Timer_Mode(const timer0_t *object);
static Std_ReturnType Register_Select(const timer0_t *object);
static uint16 preload_value = 0;

Std_ReturnType Timer0_Init(const timer0_t *object){
    Std_ReturnType ret_value=E_OK;
    if(NULL == object)
    {
        ret_value=E_NOT_OK;
    }
    else{
        TIMER0_DISABLE();
        ret_value = Prescaler_config(object);
        ret_value = Timer_Mode(object);
        ret_value = Register_Select(object);
        TMR0H = (object->preload_value) >> 8;
        TMR0L = (uint8)(object->preload_value);
        preload_value = object->preload_value;
#if TMR0_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE 
        interrupt_TMR0_t timer0_interrupt = {.TMR0_ExceptionHandler = object->timer0_ExceptionHandler,
                                             .periority = object->priority,
                                             .preload_value = object->preload_value
                                            };
        Interrupt_TMR0_Enable(&timer0_interrupt);
#endif
        TIMER0_ENABLE();
    }
    return ret_value;
}

Std_ReturnType Timer0_Deinit(const timer0_t *object){
     Std_ReturnType ret_value=E_OK;
    if(NULL == object)
    {
        ret_value=E_NOT_OK;
    }
    else{
#if TMR0_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE 
        interrupt_TMR0_t timer0_interrupt = {.TMR0_ExceptionHandler = object->timer0_ExceptionHandler,
                                             .periority = object->priority
                                            };
        Interrupt_TMR0_Disable(&timer0_interrupt);
#endif
        TIMER0_DISABLE();
    }
    return ret_value;
}

Std_ReturnType Timer0_Write(const timer0_t *object,uint16 value){
     Std_ReturnType ret_value=E_NOT_OK;
    if(NULL == object)
    {
        ret_value=E_NOT_OK;
    }
    else{
        TMR0H = (value) >> 8;
        TMR0L = (uint8)(value);
        ret_value=E_OK;
    }
    return ret_value;
}

Std_ReturnType Timer0_Read(const timer0_t *object,uint16 *result){
     Std_ReturnType ret_value=E_OK;
     uint8 L_Timer0 =0,H_Timer0=0;
    if(NULL == object || NULL == result)
    {
        ret_value=E_NOT_OK;
    }
    else{
        L_Timer0=TMR0L;
        H_Timer0=TMR0H;
        *result=(uint16)((H_Timer0 << 8) + L_Timer0);
         ret_value=E_OK;
    }
    return ret_value;
}


/*------------------------------------------- Helper Functions ----------------------------------------------*/

static Std_ReturnType Prescaler_config(const timer0_t *object){
      Std_ReturnType ret_value=E_OK;
    if(NULL == object )
    {
        ret_value=E_NOT_OK;
    }
    else{
        if(object->prescaler_featuer == FEATURE_ENABLE)
        {
            TIMER0_PRESCALER_ENABLE();
            TIMER0_PRESCALER_CONFIG(object->prescaler);
        }
        else if(object->prescaler_featuer == FEATURE_DISABLE)
        {
            TIMER0_PRESCALER_DISABLE();
        }
        else{
            TIMER0_PRESCALER_DISABLE();
        }
        ret_value=E_OK;
    }
    return ret_value;
}

static Std_ReturnType Timer_Mode(const timer0_t *object)
{
    Std_ReturnType ret_value=E_OK;
    if(NULL == object)
    {
        ret_value=E_NOT_OK;
    }
    else{
        if(TIMER0_COUNTER_MODE == object->mode)
        {
            TIMER0_COUNTER_MODE_ENABLE();
            if(counter_FALLING_EDGE == object->edge)        {TIMER0_FALLING_EDGE(); }
            else if(counter_RISING_EDGE == object->edge)    {TIMER0_RISING_EDGE(); }
            else{TIMER0_RISING_EDGE();}
        }
        else if(TIMER0_TIMER_MODE == object->mode)
        {
            TIMER0_TIMER_MODE_ENABLE(); 
        }
        else 
        {
            TIMER0_TIMER_MODE_ENABLE(); 
        }
        ret_value=E_OK;
    }
    return ret_value;
}

static Std_ReturnType Register_Select(const timer0_t *object){
    Std_ReturnType ret_value=E_OK;
    if(NULL == object)
    {
        ret_value=E_NOT_OK;
    }
    else{
        if(TIMER0_8BIT_REG == object->register_size)        {TIMER0_8BIT_MODE_ENABLE();}
        else if(TIMER0_16BIT_REG == object->register_size)  {TIMER0_16BIT_MODE_ENABLE();}
        else{TIMER0_8BIT_MODE_ENABLE();}
        
        ret_value = E_OK;
    }
    return ret_value;
}