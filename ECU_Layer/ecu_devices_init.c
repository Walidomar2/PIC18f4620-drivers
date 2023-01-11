/* 
 * File:   ecu_devices_init.c
 * Author: Walid Omar
 *
 * Created on December 18, 2022, 10:48 PM
 */

#include "ecu_devices_init.h"

led_config_t led_1 = {
    .led_status = LED_OFF,
    .port_index = PORTC_INDEX ,
    .pin_num =PIN0
};

led_config_t led_2= {
    .led_status = LED_OFF,
    .port_index = PORTC_INDEX ,
    .pin_num =PIN1
};
led_config_t led_3= {
    .led_status = LED_OFF,
    .port_index = PORTC_INDEX ,
    .pin_num =PIN3
};
led_config_t led_4= {
    .led_status = LED_OFF,
    .port_index = PORTC_INDEX ,
    .pin_num =PIN4
};

void modules_init(void)
{
    led_init(&led_1);
    led_init(&led_2);
    led_init(&led_3);
    led_init(&led_4);
}

