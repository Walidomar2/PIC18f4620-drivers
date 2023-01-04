/* 
 * File:   mcal_interrupt_config.h
 * Author: Walid Omar
 *
 * Created on December 31, 2022, 9:29 PM
 */

#ifndef MCAL_INTERRUPT_CONFIG_H
#define	MCAL_INTERRUPT_CONFIG_H

/* Includes Section*/
#include"../proc/pic18f4620.h"
#include"../mcal_std_types.h"
#include"../GPIO_Module/hal_gpio.h"
#include"../device_config.h"

/* Macros Declarations */
#define INTERRUPT_ENABLE    1
#define INTERRUPT_DISABLE   0

#define INTERRUPT_OCCUR     1
#define INTERRUPT_NOT_OCCUR 0

#define INTERRUPT_PERIORITY_ENABLE  1
#define INTERRUPT_PERIORITY_DISABLE 0
#define INTERRUPT_FEATURE   INTERRUPT_PERIORITY_ENABLE 

/* Macro Functions Declarations*/
#if INTERRUPT_FEATURE==INTERRUPT_PERIORITY_ENABLE
#define INTERRUPT_PRIORITY_ENABLE()     (RCONbits.IPEN=1)
#define INTERRUPT_PRIORITY_DISABLE()    (RCONbits.IPEN=0)
#define GLOBAL_INTE_HIGH_ENABLE()   (INTCONbits.GIEH=1)
#define GLOBAL_INTE_HIGH_DISABLE()  (INTCONbits.GIEH=0)
#define GLOBAL_INTE_LOW_ENABLE()    (INTCONbits.GIEL=1)
#define GLOBAL_INTE_LOW_DISABLE()   (INTCONbits.GIEL=0)

#else
#define GLOBAL_INTERRUPT_ENABLE()   (INTCONbits.GIE=1)
#define GLOBAL_INTERRUPT_DISABLE()  (INTCONbits.GIE=0)
#define PERIPHERAL_INTERRUPT_ENABLE()   (INTCONbits.PEIE=1)
#define PERIPHERAL_INTERRUPT_DISABLE()  (INTCONbits.PEIE=0)
#endif

/* Data Types Declarations */
typedef enum{
    LOW_PERIORITY =0,
    HIGH_PERIORITY       
}interrupt_periority;



/* Data Type Declaration */

#endif	/* MCAL_INTERRUPT_CONFIG_H */

