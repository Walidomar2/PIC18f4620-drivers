/* 
 * File:   ecu_relay.h
 * Author: Walid Omar
 *
 * Created on November 29, 2022, 7:55 AM
 */

/* Includes Section */
#include "ecu_relay.h"

Std_ReturnType relay_init(const relay_config_t *my_relay){
    Std_ReturnType ret_value =E_OK ;
    if(NULL == my_relay )
    {
        ret_value = E_NOT_OK; 
    }
    else
    {
        Pin_Config_t obj ={.Port = my_relay->relay_port , .Pin = my_relay->relay_pin ,
                           .Logic=my_relay->relay_status, .Direction=OUTPUT};
      ret_value = gpio_pin_init(&obj);
    
    }
    return ret_value ;
}

Std_ReturnType relay_turn_on(const relay_config_t *my_relay){
     Std_ReturnType ret_value =E_OK ;
    if(NULL == my_relay )
    {
        ret_value = E_NOT_OK; 
    }
    else
    {
        Pin_Config_t pin_obj = {.Port = my_relay->relay_port , .Pin = my_relay->relay_pin
                                ,.Direction = OUTPUT ,.Logic = my_relay->relay_status};
        
      ret_value= gpio_pin_write_logic(&pin_obj,HIGH);

    }
    return ret_value ;
}

Std_ReturnType relay_turn_off(const relay_config_t *my_relay){
     Std_ReturnType ret_value =E_OK ;
    if(NULL == my_relay )
    {
        ret_value = E_NOT_OK; 
    }
    else
    {
        Pin_Config_t pin_obj = {.Port = my_relay->relay_port , .Pin = my_relay->relay_pin
                                ,.Direction = OUTPUT ,.Logic = my_relay->relay_status};
        
      ret_value= gpio_pin_write_logic(&pin_obj,LOW);
    
    }
    return ret_value ;
}

