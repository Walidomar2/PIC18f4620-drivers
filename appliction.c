/* 
 * File:   appliction.c
 * Author: Walid Omar
 *
 * Created on November 13, 2022, 9:08 PM
 */

#include "application.h"
void RB4_HIGH_APP_ISR(void);
void RB4_LOW_APP_ISR(void);
void RB5_HIGH_APP_ISR(void);
void RB5_LOW_APP_ISR(void);

interrupt_RBx_t Interrupt_RB4 ={
    .EXT_InterruptHandlerHigh = RB4_HIGH_APP_ISR,
    .EXT_InterruptHandlerLow = RB4_LOW_APP_ISR ,
    .priority = HIGH_PRIORITY,
    .RBx_pin.Port = PORTB_INDEX,
    .RBx_pin.Pin = PIN4,
    .RBx_pin.Direction = INPUT,
    .RBx_pin.Logic = LOW
};

interrupt_RBx_t Interrupt_RB5 ={
    .EXT_InterruptHandlerHigh = RB5_HIGH_APP_ISR,
    .EXT_InterruptHandlerLow = RB5_LOW_APP_ISR ,
    .priority = HIGH_PRIORITY,
    .RBx_pin.Port = PORTB_INDEX,
    .RBx_pin.Pin = PIN5,
    .RBx_pin.Direction = INPUT,
    .RBx_pin.Logic = LOW
};


int main(){
    modules_init();
    Interrupt_RBx_Enable(&(Interrupt_RB4 ));
    while(1){
        
    }
    return (EXIT_SUCCESS);
}

void RB4_HIGH_APP_ISR(void){}
void RB4_LOW_APP_ISR(void){}
void RB5_HIGH_APP_ISR(void){}
void RB5_LOW_APP_ISR(void){}
