/* 
 * File:   ecu_button.h
 * Author: Walid Omar
 *
 * Created on November 25, 2022, 8:26 PM
 */

#ifndef ECU_BUTTON_H
#define	ECU_BUTTON_H

/* Includes Sections */
#include "../../MCAL_Layer/GPIO_Module/hal_gpio.h"

/* Data Types Declarations */
typedef enum {
    BUTTON_RELEASED ,
    BUTTON_PRESSED
}button_state_t;

typedef enum {
    BUTTON_ACTIVE_LOW ,
    BUTTON_ACTIVE_HIGH
            
}button_active_t;

typedef struct {
    Pin_Config_t    button_pin;
    button_state_t  button_state;
    button_active_t button_connection;
    
}button_config_t;

/* Macros Declarations */

/* Macro Functions Declarations*/

/* Functions Declarations */
Std_ReturnType button_init(const button_config_t *btn);
Std_ReturnType button_read(const button_config_t *btn , button_state_t *state);

#endif	/* ECU_BUTTON_H */

