/* 
 * File:   timer0.h
 * Author: Walid Omar
 *
 * Created on January 30, 2023, 3:47 PM
 */

#ifndef TIMER0_H
#define	TIMER0_H

/* Includes Section */
#include "../../MCAL_Layer/GPIO_Module/hal_gpio.h"
#include "../../MCAL_Layer/INTERRUPT/mcal_internal_interrupt.h"
 /* Macros Declarations */
#define FEATURE_ENABLE      1U
#define FEATURE_DISABLE     0

/* Macros Functions Declaration */
#define TIMER0_ENABLE()                (T0CONbits.TMR0ON = 1)
#define TIMER0_DISABLE()               (T0CONbits.TMR0ON = 0)
#define TIMER0_8BIT_MODE_ENABLE()      (T0CONbits.T08BIT = 1)
#define TIMER0_16BIT_MODE_ENABLE()     (T0CONbits.T08BIT = 0)
#define TIMER0_TIMER_MODE_ENABLE()     (T0CONbits.T0CS = 0 )
#define TIMER0_COUNTER_MODE_ENABLE()   (T0CONbits.T0CS = 1 )
#define TIMER0_FALLING_EDGE()          (T0CONbits.T0SE = 1 )
#define TIMER0_RISING_EDGE()           (T0CONbits.T0SE = 0 )
#define TIMER0_PRESCALER_DISABLE()     (T0CONbits.PSA = 1 )
#define TIMER0_PRESCALER_ENABLE()      (T0CONbits.PSA = 0 )
#define TIMER0_PRESCALER_CONFIG(_config)      (T0CONbits.T0PS = _config)

/* Data Types Declarations */

typedef enum {
    TIMER0_PRESCALER_DIV_BY_2 = 0,
    TIMER0_PRESCALER_DIV_BY_4    ,
    TIMER0_PRESCALER_DIV_BY_8    ,        
    TIMER0_PRESCALER_DIV_BY_16   ,
    TIMER0_PRESCALER_DIV_BY_32   ,
    TIMER0_PRESCALER_DIV_BY_64   ,
    TIMER0_PRESCALER_DIV_BY_128  ,   
    TIMER0_PRESCALER_DIV_BY_256  
}timer0_prescaler_value;

typedef enum{
    counter_FALLING_EDGE ,
    counter_RISING_EDGE        
}counter_edge_select;

typedef enum{
    TIMER0_TIMER_MODE ,
    TIMER0_COUNTER_MODE
}timer0_mode;

typedef enum{
    TIMER0_8BIT_REG ,
    TIMER0_16BIT_REG
}timer0_register_size;

typedef struct{
#if TMR0_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
    void (*timer0_ExceptionHandler)(void);
    interrupt_priority          priority;
#endif
    uint8 prescaler_featuer     : 1;
    timer0_prescaler_value      prescaler;
    timer0_mode                 mode;
    counter_edge_select         edge;
    timer0_register_size        register_size;
    uint16                      preload_value;
}timer0_t;

/* Functions Declarations */
Std_ReturnType Timer0_Init(const timer0_t *object);
Std_ReturnType Timer0_Deinit(const timer0_t *object);
Std_ReturnType Timer0_Write(const timer0_t *object,uint16 value);
Std_ReturnType Timer0_Read(const timer0_t *object,uint16 *result);

#endif	/* TIMER0_H */

