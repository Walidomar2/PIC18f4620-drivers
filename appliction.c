/* 
 * File:   appliction.c
 * Author: Walid Omar
 *
 * Created on November 13, 2022, 9:08 PM
 */

#include "application.h"
Std_ReturnType ret = E_NOT_OK;
volatile uint8 counter = 0;

void Timer0_Interrupt_ISR(void){
    counter ++ ;
    led_toggle(&led_1);
    if(counter == 2)
    {
        counter = 0;
        led_toggle(&led_2);
    }
    
}
timer0_t timer0 = {
    .timer0_ExceptionHandler = Timer0_Interrupt_ISR ,
    .preload_value = 55536,
    .priority = HIGH_PRIORITY ,
    .mode =  TIMER0_TIMER_MODE ,
    .prescaler = TIMER0_PRESCALER_DIV_BY_4 ,
    .prescaler_featuer = FEATURE_DISABLE,
    .register_size = TIMER0_16BIT_REG
};


int main(){
    modules_init();
    Timer0_Init(&timer0);
    while(1){
    }
    return (EXIT_SUCCESS);
}

