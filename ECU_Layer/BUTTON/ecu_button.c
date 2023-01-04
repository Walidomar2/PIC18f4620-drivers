/* 
 * File:   ecu_button.c
 * Author: Walid Omar
 *
 * Created on November 25, 2022, 8:26 PM
 */

#include "ecu_button.h"

Std_ReturnType button_init(const button_config_t *btn){
    
    Std_ReturnType ret_value =E_OK;
    if(NULL == btn)
    {
        ret_value =E_NOT_OK;
    }
    else
    {
       ret_value = gpio_pin_init(&(btn->button_pin));
       
    }
    
    return ret_value ;
}

Std_ReturnType button_read(const button_config_t *btn , button_state_t *btn_status){
    
     Std_ReturnType ret_value =E_OK;
     *btn_status = BUTTON_RELEASED;
     Logic_t button_logic_status = LOW ;
     
    if(NULL == btn || NULL == btn_status )
    {
        ret_value =E_NOT_OK;
    }
    else
    {
        gpio_pin_read_logic(&(btn->button_pin),&button_logic_status);
        
        if(BUTTON_ACTIVE_HIGH == btn->button_connection)
        {
            if(HIGH == button_logic_status)
            {
                *btn_status = BUTTON_PRESSED;
            }
            else
            {
                *btn_status = BUTTON_RELEASED;
            }
        }
        else if(BUTTON_ACTIVE_LOW == btn->button_connection)
        {
            if(HIGH == button_logic_status)
            {
                *btn_status = BUTTON_RELEASED;
            }
            else
            {
                *btn_status = BUTTON_PRESSED;
            }
        }
        else{/* NOTHING */}
    }
    
    return ret_value ;
}
