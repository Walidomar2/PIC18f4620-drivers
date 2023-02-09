/* 
 * File:   timer3.h
 * Author: Walid Omar
 *
 * Created on February 9, 2023, 2:20 PM
 */

#ifndef TIMER3_H
#define	TIMER3_H

/* Includes Section */
#include "../../MCAL_Layer/GPIO_Module/hal_gpio.h"
#include "../../MCAL_Layer/INTERRUPT/mcal_internal_interrupt.h"
/* Macros Declarations */
#define TIMER3_TIMER_MODE       0
#define TIMER3_COUNTER_MODE     1

#define TIMER3_SYNC_COUNTER     0
#define TIMER3_ASYNC_COUNTER    1

#define TIMER3_PRESCALER_DIV_BY_1   0
#define TIMER3_PRESCALER_DIV_BY_2   1
#define TIMER3_PRESCALER_DIV_BY_4   2
#define TIMER3_PRESCALER_DIV_BY_8   3

#define TIMER3_8BIT_REG    0
#define TIMER3_16BIT_REG   1

/* Macro Functions Declarations */
#define TIMER3_ENABLE()         (T3CONbits.TMR3ON = 1 )
#define TIMER3_DISABLE()        (T3CONbits.TMR3ON = 0 )

#define TIMER3_TIMER_MODE_ENABLE()          (T3CONbits.TMR3CS = 0 )
#define TIMER3_COUNTER_MODE_ENABLE()        (T3CONbits.TMR3CS = 1 )

#define TIMER3_SYNC_COUNTER_MODE()          (T3CONbits.T3SYNC = 0 )
#define TIMER3_ASYNC_COUNTER_MODE()         (T3CONbits.T3SYNC = 1 )

#define TIMER3_PRESCALER_CONFIG(_config)    (T3CONbits.T3CKPS = _config );

#define TIMER3_REG_16BIT_FORMAT()       (T3CONbits.RD16 = 1 )
#define TIMER3_REG_8BIT_FORMAT()        (T3CONbits.RD16 = 0 )

/* Data Type Declarations */

typedef struct{
    #if TMR3_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
    void (*timer3_ExceptionHandler)(void);
    interrupt_priority          priority;
    #endif
    uint16  preload_value; 
    uint8   prescaler : 2;
    uint8   mode : 1;
    uint8   synchronization : 1;
    uint8   format :1;
    uint8   reserved : 3;
}timer3_t;

/* Functions Declarations */
Std_ReturnType Timer3_Init(const timer3_t *t3_obj);
Std_ReturnType Timer3_Deinit(const timer3_t *t3_obj);
Std_ReturnType Timer3_Write(const timer3_t *t3_obj ,uint16 value);
Std_ReturnType Timer3_Read(const timer3_t *t3_obj ,uint16 *value);


#endif	/* TIMER3_H */

