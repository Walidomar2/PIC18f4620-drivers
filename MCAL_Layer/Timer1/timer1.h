/* 
 * File:   timer1.h
 * Author: Walid Omar
 *
 * Created on February 6, 2023, 11:16 AM
 */

#ifndef TIMER1_H
#define	TIMER1_H

/* Includes Section */
#include "../../MCAL_Layer/GPIO_Module/hal_gpio.h"
#include "../../MCAL_Layer/INTERRUPT/mcal_internal_interrupt.h"
#include "../../MCAL_Layer/INTERRUPT/mcal_interrupt_manager.h"

/* Macros Declarations */
#define FEATURE_ENABLE      1U
#define FEATURE_DISABLE     0

#define TIMER1_PRESCALER_DIV_BY_1   0
#define TIMER1_PRESCALER_DIV_BY_2   1
#define TIMER1_PRESCALER_DIV_BY_4   2
#define TIMER1_PRESCALER_DIV_BY_8   3

#define TIMER1_TIMER_MODE      0
#define TIMER1_COUNTER_MODE    1

#define TIMER1_SYNC_COUNTER  0
#define TIMER1_ASYNC_COUNTER 1

#define TIMER1_EXT_OSC_DISABLE  0
#define TIMER1_EXT_OSC_ENABLE   1

#define TIMER1_8BIT_REG    0
#define TIMER1_16BIT_REG   1

/* Macro Functions Declarations */
#define TIMER1_ENABLE()         (T1CONbits.TMR1ON = 1 )
#define TIMER1_DISABLE()        (T1CONbits.TMR1ON = 0 )

#define TIMER1_COUNTER_MODE_ENABLE()        (T1CONbits.TMR1CS = 1 )
#define TIMER1_TIMER_MODE_ENABLE()          (T1CONbits.TMR1CS = 0 )

#define TIMER1_SYNCH_COUNTER()          (T1CONbits.T1SYNC = 0 )
#define TIMER1_ASYNCH_COUNTER()         (T1CONbits.T1SYNC = 1 )

#define TIMER1_OSC_ENABLE()      (T1CONbits.T1OSCEN = 1 )
#define TIMER1_OSC_DISABLE()     (T1CONbits.T1OSCEN = 0 )

#define TIMER1_PRESCALER_CONFIG(_config)        (T1CONbits.T1CKPS = _config )

#define TIMER1_SYSTEM_CLK_STATUS()      (T1CONbits.T1RUN)

#define TIMER1_REG_16BIT_FORMAT()       (T1CONbits.RD16 = 1 )
#define TIMER1_REG_8BIT_FORMAT()        (T1CONbits.RD16 = 0 )

/* Data Types Declaration */

typedef struct{
    #if TMR1_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
    void (*timer1_ExceptionHandler)(void);
    interrupt_priority          priority;
    #endif
    uint8   prescaler : 2;
    uint8   mode : 1;
    uint8   synchronization : 1;
    uint8   ext_osc_config : 1;
    uint8   format :1;
    uint16  preload_value; 
    uint8   reserved : 2;
}timer1_t;

/* Functions Declarations */
Std_ReturnType Timer1_Init(const timer1_t *t1_object);
Std_ReturnType Timer1_Deinit(const timer1_t *t1_object);
Std_ReturnType Timer1_Write(const timer1_t *t1_object ,uint16 value);
Std_ReturnType Timer1_Read(const timer1_t *t1_object ,uint16 *value);

#endif	/* TIMER1_H */

