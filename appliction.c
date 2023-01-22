/* 
 * File:   appliction.c
 * Author: Walid Omar
 *
 * Created on November 13, 2022, 9:08 PM
 */

#include "application.h"
Std_ReturnType ret = E_NOT_OK;
uint16 adc_1_res= 0;

adc_config_t adc_1 =
{
    .ADC_InterruptHandler = NULL,
    .channel = ADC_CHANNEL_AN0,
    .acqu_time = ADC_12_TAD,
    .clk_select = ADC_FOSC_DIV_16 ,
    .res_format = ADC_RIGHT_RESULT ,
    .volt_sou_sel = ADC_VOLTAGE_REFERENCE_DISABLE 
};

int main(){
    modules_init();
    ADC_Init(&adc_1);
    while(1){
        ADC_ResultRead(&adc_1,&adc_1_res); 
    }
    return (EXIT_SUCCESS);
}


