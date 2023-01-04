/* 
 * File:   ecu_dc_motor.c
 * Author: Walid Omar
 *
 * Created on December 2, 2022, 10:10 AM
 */

#include "ecu_dc_motor.h"



Std_ReturnType dc_motor_init(const dc_motor_t * my_motor){
    Std_ReturnType ret_value=E_OK;
    if(NULL == my_motor)
    {
         ret_value=E_NOT_OK;
    }
    else
    {
      
        gpio_pin_init(&(my_motor->dc_motor[0]));
        gpio_pin_init(&(my_motor->dc_motor[1]));
        
    }
    return ret_value;
}

Std_ReturnType dc_motor_move_forward(const dc_motor_t * my_motor){
    Std_ReturnType ret_value=E_OK;
    if(NULL == my_motor)
    {
         ret_value=E_NOT_OK;
    }
    else
    {
       
        gpio_pin_write_logic(&(my_motor->dc_motor[0]),HIGH);
        gpio_pin_write_logic(&(my_motor->dc_motor[1]),LOW);
    }
    return ret_value;
}

Std_ReturnType dc_motor_move_backward(const dc_motor_t * my_motor){
    Std_ReturnType ret_value=E_OK;
    if(NULL == my_motor)
    {
         ret_value=E_NOT_OK;
    }
    else
    {
       
        gpio_pin_write_logic(&(my_motor->dc_motor[0]),LOW);
        gpio_pin_write_logic(&(my_motor->dc_motor[1]),HIGH);
    }
    return ret_value;
}

Std_ReturnType dc_motor_off(const dc_motor_t * my_motor){
    Std_ReturnType ret_value=E_OK;
    if(NULL == my_motor)
    {
         ret_value=E_NOT_OK;
    }
    else
    {
       
        gpio_pin_write_logic(&(my_motor->dc_motor[0]),LOW);
        gpio_pin_write_logic(&(my_motor->dc_motor[1]),LOW);
    }
    return ret_value;
}
