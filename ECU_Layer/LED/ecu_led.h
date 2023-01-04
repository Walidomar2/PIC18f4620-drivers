/* 
 * File:   ecu_led.h
 * Author: Walid Omar
 *
 * Created on November 14, 2022, 7:50 PM
 */

#ifndef ECU_LED_H
#define	ECU_LED_H
/* Includes Sections */
#include "../../MCAL_Layer/GPIO_Module/hal_gpio.h"

/* Data Types Declarations */

typedef enum {
    LED_OFF ,
    LED_ON

}led_status_t;

typedef struct {
    uint8 port_index  :4 ;
    uint8 pin_num     :3 ;
    uint8 led_status  :1 ;
}led_config_t;

/* Macros Declarations */

/* Macro Functions Declarations*/

/* Functions Declarations */
Std_ReturnType led_init(const led_config_t *led);
Std_ReturnType led_turn_on(const led_config_t *led);
Std_ReturnType led_turn_off(const led_config_t *led);
Std_ReturnType led_toggle(const led_config_t *led);

#endif	/* ECU_LED_H */

