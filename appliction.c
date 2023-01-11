/* 
 * File:   appliction.c
 * Author: Walid Omar
 *
 * Created on November 13, 2022, 9:08 PM
 */

#include "application.h"
void INT2_APP_ISR(void);
interrupt_INTx_t Interrupt_INT2 = {
    .EXT_InterruptHandler = INT2_APP_ISR ,
    .edge = INTERRUPT_FALLING_EDGE ,
    .priority = HIGH_PRIORITY,
    .INTx_pin.Port = PORTB_INDEX ,
    .INTx_pin.Pin = PIN2,
    .INTx_pin.Direction = INPUT ,
    .INTx_pin.Logic = LOW 
};

int main(){
    modules_init();
    Interrupt_INTx_Enable(&Interrupt_INT2);
    while(1){
        
        
   }
    
    return (EXIT_SUCCESS);
}
void INT2_APP_ISR(void)
{
    led_toggle(&led_1);
}

