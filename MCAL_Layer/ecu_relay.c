/* 
 * File:   Relay.h
 * Author: Walid Omar
 *
 * Created on November 29, 2022, 7:55 AM
 */

/* Includes Section */

#include "../ECU_Layer/RELAY/ecu_Relay.h"


Std_ReturnType relay_init(const relay_config_t *my_relay){
    Std_ReturnType ret_value =E_OK ;
    if(NULL == my_relay )
    {
        ret_value = E_NOT_OK; 
    }
    else
    {
        Pin_Config_t obj ={.Port = my_relay->relay_port , .Pin = my_relay->relay_pin ,
                           .Logic=my_relay->relay_status, .Direction =INPUT};
        gpio_pin_init(&obj);
    
    }
    return ret_value ;
}

Std_ReturnType relay_on(const relay_config_t *my_relay){
     Std_ReturnType ret_value =E_OK ;
    if(NULL == my_relay )
    {
        ret_value = E_NOT_OK; 
    }
    else
    {
        
    
    }
    return ret_value ;
}

Std_ReturnType relay_off(const relay_config_t *my_relay){
     Std_ReturnType ret_value =E_OK ;
    if(NULL == my_relay )
    {
        ret_value = E_NOT_OK; 
    }
    else
    {
    
    }
    return ret_value ;
}