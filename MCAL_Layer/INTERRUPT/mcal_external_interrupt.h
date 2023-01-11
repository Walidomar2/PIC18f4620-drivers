/* 
 * File:   mcal_external_interrupt.h
 * Author: Walid Omar
 *
 * Created on December 31, 2022, 9:23 PM
 */

#ifndef MCAL_EXTERNAL_INTERRUPT_H
#define	MCAL_EXTERNAL_INTERRUPT_H

/* Includes Section */
#include "mcal_interrupt_config.h"

/* Macro Functions Declarations*/

// INT0 interrupt bits configurations macros 
#define EXT_INTERRUPT_INT0_ENABLE()         (INTCONbits.INT0IE=1)
#define EXT_INTERRUPT_INT0_DISABLE()        (INTCONbits.INT0E=0)
#define EXT_INTERRUPT_INT0_SET_FLAG()       (INTCONbits.INT0IF=1)
#define EXT_INTERRUPT_INT0_CLEAR_FLAG()     (INTCONbits.INT0IF=0)
#define EXT_INTERRUPT_INT0_RISE_EDGE()      (INTCON2bits.INTEDG0=1)
#define EXT_INTERRUPT_INT0_FALL_EDGE()      (INTCON2bits.INTEDG0=0)

// INT1 interrupt bits configurations macros 
#define EXT_INTERRUPT_INT1_ENABLE()         (INTCON3bits.INT1IE=1)
#define EXT_INTERRUPT_INT1_DISABLE()        (INTCON3bits.INT1IE=0)
#define EXT_INTERRUPT_INT1_SET_FLAG()       (INTCON3bits.INT1IF=1)
#define EXT_INTERRUPT_INT1_CLEAR_FLAG()     (INTCON3bits.INT1IF=0)
#define EXT_INTERRUPT_INT1_RISE_EDGE()      (INTCON2bits.INTEDG1=1)
#define EXT_INTERRUPT_INT1_FALL_EDGE()      (INTCON2bits.INTEDG1=0)
#define EXT_INTERRUPT_INT1_HIGH_PRIORITY()  (INTCON3bits.INT1IP=1)
#define EXT_INTERRUPT_INT1_LOW_PRIORITY()   (INTCON3bits.INT1IP=0)

// INT2 interrupt bits configurations macros 
#define EXT_INTERRUPT_INT2_ENABLE()         (INTCON3bits.INT2IE=1)
#define EXT_INTERRUPT_INT2_DISABLE()        (INTCON3bits.INT2IE=0)
#define EXT_INTERRUPT_INT2_SET_FLAG()       (INTCON3bits.INT2IF=1)
#define EXT_INTERRUPT_INT2_CLEAR_FLAG()     (INTCON3bits.INT2IF=0)
#define EXT_INTERRUPT_INT2_RISE_EDGE()      (INTCON2bits.INTEDG2=1)
#define EXT_INTERRUPT_INT2_FALL_EDGE()      (INTCON2bits.INTEDG2=0)
#define EXT_INTERRUPT_INT2_HIGH_PRIORITY()  (INTCON3bits.INT2IP=1)
#define EXT_INTERRUPT_INT2_LOW_PRIORITY()   (INTCON3bits.INT2IP=0)

// On change interrupt port configurations macros 
#define EXT_INTERRUPT_RBx_ENABLE()        (INTCONbits.RBIE=1)
#define EXT_INTERRUPT_RBx_DISABLE()       (INTCONbits.RBIE=0)
#define EXT_INTERRUPT_RBx_SET_FLAG()      (INTCONbits.RBIF=1)
#define EXT_INTERRUPT_RBx_CLEAR_FLAG()    (INTCONbits.RBIF=0)
#define EXT_INTERRUPT_RBx_HIGH_PRIORITY() (INTCON2bits.RBIP=1)
#define EXT_INTERRUPT_RBx_LOW_PRIORITY()  (INTCON2bits.RBIP=0)

/* Data Type Declarations */

typedef enum {
    INTERRUPT_FALLING_EDGE =0,
    INTERRUPT_RISING_EDGE       
}interrupt_edge;

typedef struct {
    void (* EXT_InterruptHandler)(void);    // Call back function to notify through layers 
    Pin_Config_t    INTx_pin;
    interrupt_edge  edge;
    interrupt_priority priority;
}interrupt_INTx_t;

typedef struct {
    void (* EXT_InterruptHandlerHigh)(void); 
    void (* EXT_InterruptHandlerLow)(void); 
    Pin_Config_t    RBx_pin;
    interrupt_priority priority;
}interrupt_RBx_t;

/* Functions Declarations */
Std_ReturnType Interrupt_INTx_Enable(const interrupt_INTx_t *object);
Std_ReturnType Interrupt_INTx_Disable(const interrupt_INTx_t *object);
Std_ReturnType Interrupt_RBx_Enable(const interrupt_RBx_t *object);
Std_ReturnType Interrupt_RBx_Disable(const interrupt_RBx_t *object);

#endif	/* MCAL_EXTERNAL_INTERRUPT_H */

