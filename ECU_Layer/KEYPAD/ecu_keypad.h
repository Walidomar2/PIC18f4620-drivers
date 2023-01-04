/* 
 * File:   ecu_keypad.h
 * Author: Walid Omar
 *
 * Created on December 11, 2022, 11:35 PM
 */

#ifndef ECU_KEYPAD_H
#define	ECU_KEYPAD_H

/* Includes Section */
#include "../../MCAL_Layer/GPIO_Module/hal_gpio.h"
/* Macros Declarations */
#define KEYPAD_ROWS     4
#define KEYPAD_COLUMNS  4

/* Data Types Declarations */

typedef struct {
    Pin_Config_t keypad_rows[KEYPAD_ROWS];
    Pin_Config_t keypad_columns[KEYPAD_COLUMNS];
}keypad_config_t;

uint8 flag = 0;

/* Functions Declarations */

Std_ReturnType keypad_init(const keypad_config_t *my_keypad);
Std_ReturnType keypad_read(const keypad_config_t *my_keypad,uint8 *value);

#endif	/* ECU_KEYPAD_H */

