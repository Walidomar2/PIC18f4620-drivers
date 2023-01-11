/* 
 * File:   ecu_devices_init.h
 * Author: Walid Omar
 *
 * Created on December 18, 2022, 10:48 PM
 */

#ifndef ECU_DEVICES_INIT_H
#define	ECU_DEVICES_INIT_H

/*Includes Sections*/

#include "LED/ecu_led.h"
#include "BUTTON/ecu_button.h"
#include "RELAY/ecu_relay.h"
#include "DC_MOTOR/ecu_dc_motor.h"
#include "SEVEN_Segment/ecu_seven_segment.h"
#include "KEYPAD/ecu_keypad.h"
#include "LCD/ecu_lcd.h"

extern led_config_t led_1;
extern led_config_t led_2;
void modules_init(void);


#endif	/* ECU_DEVICES_INIT_H */

