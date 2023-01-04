/* 
 * File:   ecu_relay.h
 * Author: Walid Omar
 *
 * Created on November 29, 2022, 8:25 AM
 */

#ifndef ECU_RELAY_H
#define	ECU_RELAY_H

/* Includes Section */

#include "../../MCAL_Layer/GPIO_Module/hal_gpio.h"

/* Data Types Declarations */

typedef enum {
    RELAY_OFF,
    RELAY_ON
        
}relay_status;

typedef struct {
   uint8 relay_port :4 ;
   uint8 relay_pin  :3;
   uint8 relay_status :1;
   
}relay_config_t;

/* Macros Declarations */

/* Macro Functions Declarations*/

/* Functions Declarations */

Std_ReturnType relay_init(const relay_config_t *my_relay);
Std_ReturnType relay_turn_on(const relay_config_t *my_relay);
Std_ReturnType relay_turn_off(const relay_config_t *my_relay);

#endif	/* ECU_RELAY_H */

