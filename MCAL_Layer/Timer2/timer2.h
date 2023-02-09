/* 
 * File:   timer2.h
 * Author: Walid Omar
 *
 * Created on February 9, 2023, 1:19 PM
 */

#ifndef TIMER2_H
#define	TIMER2_H

/* Includes Sections */
#include "../../MCAL_Layer/GPIO_Module/hal_gpio.h"
#include "../../MCAL_Layer/INTERRUPT/mcal_internal_interrupt.h"

/* Macros Declarations */
#define TIMER2_PRESCALER_DIV_BY_1   0
#define TIMER2_PRESCALER_DIV_BY_4   1
#define TIMER2_PRESCALER_DIV_BY_16  2

#define TIMER2_POSTSCALER_DIV_BY_1       0
#define TIMER2_POSTSCALER_DIV_BY_2       1
#define TIMER2_POSTSCALER_DIV_BY_3       2
#define TIMER2_POSTSCALER_DIV_BY_4       3
#define TIMER2_POSTSCALER_DIV_BY_5       4
#define TIMER2_POSTSCALER_DIV_BY_6       5
#define TIMER2_POSTSCALER_DIV_BY_7       6
#define TIMER2_POSTSCALER_DIV_BY_8       7
#define TIMER2_POSTSCALER_DIV_BY_9       8
#define TIMER2_POSTSCALER_DIV_BY_10      9
#define TIMER2_POSTSCALER_DIV_BY_11      10
#define TIMER2_POSTSCALER_DIV_BY_12      11
#define TIMER2_POSTSCALER_DIV_BY_13      12
#define TIMER2_POSTSCALER_DIV_BY_14      13
#define TIMER2_POSTSCALER_DIV_BY_15      14
#define TIMER2_POSTSCALER_DIV_BY_16      15

/* Macro Functions Declarations */
#define TIMER2_ENABLE()         (T2CONbits.TMR2ON = 1 )
#define TIMER2_DISABLE()        (T2CONbits.TMR2ON = 0 )

#define TIMER2_PRESCALER_CONFIG(_config)        (T2CONbits.T2CKPS = _config)
#define TIMER2_POSTSCALER_CONFIG(_config)       (T2CONbits.TOUTPS = _config)
/* Data Types Declarations */

typedef struct{
    #if TMR2_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
    void (*timer2_ExceptionHandler)(void);
    interrupt_priority          priority;
    #endif
    uint8   proload_value;
    uint8   postscaler :4;
    uint8   prescaler :2;
    uint8   reserved :2;
}timer2_t;
/* Functions Declarations */
Std_ReturnType Timer2_Init(const timer2_t *t2_obj);
Std_ReturnType Timer2_DeInit(const timer2_t *t2_obj);
Std_ReturnType Timer2_Write(const timer2_t *t2_obj, uint8 value);
Std_ReturnType Timer2_Read(const timer2_t *t2_obj, uint8 *value);
#endif	/* TIMER2_H */

