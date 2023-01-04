/* 
 * File:   hal_gpio.h
 * Author: Walid Omar 
 * 
 * Created on November 13, 2022, 9:28 PM
 */

#ifndef HAL_GPIO_H
#define	HAL_GPIO_H

/* Includes Sections */

#include "../proc/pic18f4620.h"
#include "../mcal_std_types.h"
#include "../device_config.h"

/* Data Types Declarations */

typedef enum{
    LOW ,
    HIGH       
}Logic_t;

typedef enum{
    OUTPUT,
    INPUT
}Direction_t;

typedef enum{
    PIN0 =0,
    PIN1,
    PIN2,
    PIN3,
    PIN4,
    PIN5,
    PIN6,
    PIN7
}Pin_Index_t;

typedef enum{
    PORTA_INDEX =0,
    PORTB_INDEX ,
    PORTC_INDEX,
    PORTD_INDEX,
    PORTE_INDEX,
     
}Port_Index_t;

typedef struct{
    uint8 Port      :3 ;
    uint8 Pin       :3 ;
    uint8 Direction :1;
    uint8 Logic     :1;
    
}Pin_Config_t;

/* Macros Declarations */

#define PIN_MAX_NUMBER      8
#define PORT_MAX_NUMBER     5
#define PORT_MASK           0XFF

/* Macro Functions Declarations*/

#define HWREG8(_X) (*(( volatile char *)(_X)))
#define W_TRISC (HWREG8(0xF94))
#define W_LATC (HWREG8(0xF8B))

#define SET_BIT(REG,BIT_POS)    (REG |= (1 << BIT_POS))
#define CLEAR_BIT(REG,BIT_POS)  (REG &= ~(1 << BIT_POS))
#define TOGGLE_BIT(REG,BIT_POS) (REG ^= (1 << BIT_POS))
#define READ_BIT(REG,BIT_POS)   ((REG >> BIT_POS)& 1)

/* Functions Declarations */
Std_ReturnType gpio_pin_direction_init(const Pin_Config_t *_pin_config);
Std_ReturnType gpio_pin_init(const Pin_Config_t *_pin_config);
Std_ReturnType gpio_pin_get_direction_status(const Pin_Config_t *_pin_config ,Direction_t *dir_status);
Std_ReturnType gpio_pin_write_logic(const Pin_Config_t *_pin_config , Logic_t logic);
Std_ReturnType gpio_pin_read_logic(const Pin_Config_t *_pin_config , Logic_t *logic);
Std_ReturnType gpio_pin_toggle(const Pin_Config_t *_pin_config);

Std_ReturnType gpio_port_init(Port_Index_t port , uint8 dir);
Std_ReturnType gpio_port_get_direction_status(Port_Index_t port ,uint8 *dir_status);
Std_ReturnType gpio_port_write_logic(Port_Index_t port , uint8 logic);
Std_ReturnType gpio_port_read_logic(Port_Index_t port , uint8 *logic);
Std_ReturnType gpio_port_toggle(Port_Index_t port);

#endif	/* HAL_GPIO_H */

