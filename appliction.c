/* 
 * File:   appliction.c
 * Author: Walid Omar
 *
 * Created on November 13, 2022, 9:08 PM
 */

#include "application.h"
#include "MCAL_Layer/Timer3/timer3.h"

Std_ReturnType ret = E_NOT_OK;
void Timer1_ISR(void)
{
    led_toggle(&led_1);
}
timer1_t timer1_obj={
    .timer1_ExceptionHandler = Timer1_ISR,
    .mode = TIMER1_TIMER_MODE,
    .preload_value = 3000,
    .prescaler = TIMER1_PRESCALER_DIV_BY_8 ,
    .format = TIMER1_16BIT_REG
};

int main(){
    modules_init();
    Timer1_Init(&timer1_obj);
    while(1){
        
    }
    return (EXIT_SUCCESS);
}

