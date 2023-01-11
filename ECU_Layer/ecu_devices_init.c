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

void modules_init(void)
{
    led_init(&led_1);
}

