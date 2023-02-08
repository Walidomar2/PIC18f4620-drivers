/* 
 * File:   appliction.c
 * Author: Walid Omar
 *
 * Created on November 13, 2022, 9:08 PM
 */

#include "application.h"

Std_ReturnType ret = E_NOT_OK;
volatile uint8 counter = 0;
void Timer1_Interrupt_ISR(void){
    led_turn_on(&led_1);
    counter++;
}

timer1_t timer1_obj={
    .timer1_ExceptionHandler = Timer1_Interrupt_ISR,
    .prescaler = TIMER1_PRESCALER_DIV_BY_8,
    .mode = TIMER1_TIMER_MODE,
    .format = TIMER1_8BIT_REG,
    .preload_value = 3036,
    .priority = HIGH_PRIORITY,
    .ext_osc_config = TIMER1_EXT_OSC_DISABLE
};

int main(){
    modules_init();
    Timer1_Init( &timer1_obj );

    while(1){
        
    }
    return (EXIT_SUCCESS);
}

