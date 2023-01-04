/* 
 * File:   ecu_led.c
 * Author: Walid Omar
 *
 * Created on November 14, 2022, 7:47 PM
 */

#include "ecu_led.h"

Std_ReturnType led_init(const led_config_t *led){
    
    Std_ReturnType ret_value =E_OK ;
    
    if(NULL == led)
    {
        ret_value =E_NOT_OK ;
    }
    else
    {
        Pin_Config_t pin_obj = {.Port = led->port_index , .Pin = led->pin_num
                                ,.Direction = OUTPUT ,.Logic = led->led_status };
        
      ret_value= gpio_pin_init(&pin_obj);
     
    }
    return ret_value ;
}


Std_ReturnType led_turn_on(const led_config_t *led){
    
     Std_ReturnType ret_value =E_OK ;
    
    if(NULL == led)
    {
        ret_value =E_NOT_OK ;
    }
    else
    {
        Pin_Config_t pin_obj = {.Port = led->port_index , .Pin = led->pin_num
                                ,.Direction = OUTPUT ,.Logic = led->led_status };
        
      ret_value= gpio_pin_write_logic(&pin_obj,HIGH);
    
    }
    return ret_value ;
}


Std_ReturnType led_turn_off(const led_config_t *led){
    
     Std_ReturnType ret_value =E_OK ;
    
    if(NULL == led)
    {
        ret_value =E_NOT_OK ;
    }
    else
    {
        Pin_Config_t pin_obj = {.Port = led->port_index , .Pin = led->pin_num
                                ,.Direction = OUTPUT ,.Logic = led->led_status };
        
      ret_value= gpio_pin_write_logic(&pin_obj,LOW);
    }
    return ret_value ;
}


Std_ReturnType led_toggle(const led_config_t *led){
    
     Std_ReturnType ret_value =E_OK ;
    
    if(NULL == led)
    {
        ret_value =E_NOT_OK ;
    }
    else
    {
        Pin_Config_t pin_obj = {.Port = led->port_index , .Pin = led->pin_num
                                ,.Direction = OUTPUT ,.Logic = led->led_status };
        
      ret_value= gpio_pin_toggle(&pin_obj);
    
    }
    return ret_value ;
}