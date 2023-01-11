/* 
 * File:   mcal_interrupt_manager.c
 * Author: Walid Omar
 *
 * Created on December 31, 2022, 9:22 PM
 */

#include "mcal_interrupt_manager.h"

#if INTERRUPT_FEATURE == INTERRUPT_PRIORITY_ENABLE
void __interrupt InterruptManagerHigh(void){
    
}

void __interrupt(low_priority) InterruptManagerLow(void){
    
}


#else
void __interrupt()InterruptManager(void){
    if((INTERRUPT_ENABLE == INTCONbits.INT0IE) && (INTERRUPT_OCCUR == INTCONbits.INT0IF))
    {
        INT0_ISR();
    }
    else{ /*Nohting*/ }
    
    if((INTERRUPT_ENABLE == INTCON3bits.INT1IE)&&(INTERRUPT_OCCUR == INTCON3bits.INT1IF))
    {
        INT1_ISR();
    }
    else{ /* Nothing */}
    
    if((INTERRUPT_ENABLE == INTCON3bits.INT2IE)&&(INTERRUPT_OCCUR == INTCON3bits.INT2IF))
    {
        INT2_ISR();
    }
    else{ /* Nothing */}
}


#endif
