/* 
 * File:   ecu_seven_segment.h
 * Author: Walid Omar
 *
 * Created on December 6, 2022, 10:38 AM
 */

#include "ecu_seven_segment.h"

Std_ReturnType seven_segment_init(const segment_config_t *my_segment){
    Std_ReturnType ret_value=E_OK;
    
    if(NULL == my_segment)
    {
        ret_value=E_NOT_OK;
    }
    else
    {
        gpio_pin_init(&(my_segment->segment_pins[0]));
        gpio_pin_init(&(my_segment->segment_pins[1]));
        gpio_pin_init(&(my_segment->segment_pins[2]));
        gpio_pin_init(&(my_segment->segment_pins[3]));

    }
    return ret_value;
}

Std_ReturnType seven_segment_write_number(const segment_config_t *my_segment ,uint8 number){
     Std_ReturnType ret_value=E_OK;
    
    if((NULL == my_segment)||(number > 9 ))
    {
        ret_value=E_NOT_OK;
    }
    else
    {
        gpio_pin_write_logic(&(my_segment->segment_pins[0]),number&0x01);
        gpio_pin_write_logic(&(my_segment->segment_pins[1]),(number >> 1) &0x01);
        gpio_pin_write_logic(&(my_segment->segment_pins[2]),(number >> 2) &0x01);
        gpio_pin_write_logic(&(my_segment->segment_pins[3]),(number >> 3) &0x01);
    
    }
    return ret_value;

}
