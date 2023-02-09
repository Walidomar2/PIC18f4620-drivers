/* 
 * File:   mcal_interrupt_manager.c
 * Author: Walid Omar
 *
 * Created on December 31, 2022, 9:22 PM
 */

#include "mcal_interrupt_manager.h"

#if INTERRUPT_FEATURE == INTERRUPT_PRIORITY_ENABLE

void __interrupt()InterruptManagerHigh(void){
    
    if((PIE1bits.TMR1IE == INTERRUPT_ENABLE)&&(PIR1bits.TMR1IF == INTERRUPT_OCCUR))
    {
        TMR1_ISR();
    }
    else {/* Nothing */}
}

void __interrupt(low_priority) InterruptManagerLow(void){
 
}


#else
void __interrupt()InterruptManager(void){
    
     if((INTERRUPT_ENABLE == PIE1bits.TMR1IE ) && (INTERRUPT_OCCUR == PIR1bits.TMR1IF))
    {
        TMR1_ISR();
    }
    else{ /*Nohting*/ }
     
    if((INTERRUPT_ENABLE ==PIE1bits.TMR2IE ) && (INTERRUPT_OCCUR ==PIR1bits.TMR2IF))
    {
        TMR2_ISR();
    }
    else{ /*Nohting*/ }
    
    if((INTERRUPT_ENABLE ==PIE2bits.TMR3IE ) && (INTERRUPT_OCCUR ==PIR2bits.TMR3IF))
    {
        TMR3_ISR();
    }
    else{ /*Nohting*/ }
    
}


#endif
