/* 
 * File:   mcal_interrupt_manager.h
 * Author: Walid Omar
 *
 * Created on December 31, 2022, 9:22 PM
 */

#ifndef MCAL_INTERRUPT_MANAGER_H
#define	MCAL_INTERRUPT_MANAGER_H

/* Includes Section */
#include "mcal_interrupt_config.h"

/* Function Declarations */
void INT0_ISR(void);
void INT1_ISR(void);
void INT2_ISR(void);
void RB4_ISR(uint8 logic);
void RB5_ISR(uint8 logic);
void RB6_ISR(uint8 logic);
void RB7_ISR(uint8 logic);




#endif	/* MCAL_INTERRUPT_MANAGER_H */

