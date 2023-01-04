/* 
 * File:   hal_gpio.c
 * Author: Walid Omar
 *
 * Created on November 13, 2022, 9:08 PM
 */

#include "hal_gpio.h"

volatile uint8 *tris_regs[]={&TRISA,&TRISB,&TRISC,&TRISD,&TRISE};
volatile uint8 *lat_regs[]={&LATA,&LATB,&LATC,&LATD,&LATE};
volatile uint8 *port_regs[]={&PORTA,&PORTB,&PORTC,&PORTD,&PORTE};

Std_ReturnType gpio_pin_direction_init(const Pin_Config_t *_pin_config){
     
    Std_ReturnType ret_value =E_OK ;
    
    if(( NULL == _pin_config ) || (_pin_config->Pin > PIN_MAX_NUMBER -1 ) || (_pin_config->Port > PORT_MAX_NUMBER -1))
    {
        ret_value = E_NOT_OK ;
    }
    else
    {
        switch(_pin_config->Direction){   
             case OUTPUT:
                 CLEAR_BIT(*tris_regs[_pin_config->Port],_pin_config->Pin);
                 break;
                    
             case INPUT:
                 SET_BIT(*tris_regs[_pin_config->Port],_pin_config->Pin);
                 break;
               
             default :   ret_value = E_NOT_OK ;  
          }
     }
    
    return ret_value;

}


Std_ReturnType gpio_pin_init(const Pin_Config_t *_pin_config){
    
    Std_ReturnType ret_value =E_OK ;
    
    if(( NULL == _pin_config ) || (_pin_config->Pin > PIN_MAX_NUMBER -1 ) || (_pin_config->Port > PORT_MAX_NUMBER -1))
    {
        ret_value = E_NOT_OK ;
    }
    else
    {
        switch(_pin_config->Direction){   
             case OUTPUT:
                 CLEAR_BIT(*tris_regs[_pin_config->Port],_pin_config->Pin);
                 break;
                    
             case INPUT:
                 SET_BIT(*tris_regs[_pin_config->Port],_pin_config->Pin);
                 break;
               
             default :   ret_value = E_NOT_OK ;  
          }
        ret_value = gpio_pin_write_logic(_pin_config,_pin_config->Logic);
     }
    
    return ret_value;
}

Std_ReturnType gpio_pin_get_direction_status(const Pin_Config_t *_pin_config ,Direction_t *dir_status){
    
    Std_ReturnType ret_value =E_OK;
    
    if(( NULL == _pin_config ) || (NULL == dir_status) || (_pin_config->Pin > PIN_MAX_NUMBER -1 ) || (_pin_config->Port > PORT_MAX_NUMBER -1))
    {
        ret_value=E_NOT_OK ;
        
    }
    else
    {
        *dir_status = READ_BIT(*tris_regs[_pin_config->Port],_pin_config->Pin); 
    }
    return ret_value ;
}

Std_ReturnType gpio_pin_write_logic(const Pin_Config_t *_pin_config , Logic_t logic){
    
     Std_ReturnType ret_value =E_OK ;
    
    if(( NULL == _pin_config ) || (_pin_config->Pin > PIN_MAX_NUMBER -1 ) || (_pin_config->Port > PORT_MAX_NUMBER -1))
    {
        ret_value = E_NOT_OK ;
    }
    else
    {
        switch(logic){   
             case LOW:
                 CLEAR_BIT(*lat_regs[_pin_config->Port],_pin_config->Pin);
                // _pin_config->Logic = LOW ;
                 break;
                    
             case HIGH:
                 SET_BIT(*lat_regs[_pin_config->Port],_pin_config->Pin);
                 //_pin_config->Logic = HIGH;
                 break;
               
             default :   ret_value = E_NOT_OK ;  
          }
     }
    
    return ret_value;
    
}

Std_ReturnType gpio_pin_read_logic(const Pin_Config_t *_pin_config , Logic_t *logic){
    
    Std_ReturnType ret_value =E_OK;
    
    if(( NULL == _pin_config ) || (NULL == logic) || (_pin_config->Pin > PIN_MAX_NUMBER -1 ) || (_pin_config->Port > PORT_MAX_NUMBER -1))
    {
        ret_value=E_NOT_OK ;
        
    }
    else
    {
        *logic= READ_BIT(*port_regs[_pin_config->Port],_pin_config->Pin); 
    }
    return ret_value ;
    
}

Std_ReturnType gpio_pin_toggle(const Pin_Config_t *_pin_config){
    
       Std_ReturnType ret_value =E_OK ;
    
    if(( NULL == _pin_config ) || (_pin_config->Pin > PIN_MAX_NUMBER -1 ) || (_pin_config->Port > PORT_MAX_NUMBER -1))
    {
        ret_value = E_NOT_OK ;
    }
    else
    {
        TOGGLE_BIT(*lat_regs[_pin_config->Port],_pin_config->Pin);
    }
    
    return ret_value;

}



Std_ReturnType gpio_port_init(Port_Index_t port , uint8 dir){
    
    Std_ReturnType ret_value =E_OK;
    
    if(port > PORT_MAX_NUMBER-1)
    {
        ret_value =E_NOT_OK;
    }
    else
    {
        *tris_regs[port] = dir ;
    }
    
    return ret_value;
}

Std_ReturnType gpio_port_get_direction_status(Port_Index_t port ,uint8 *dir_status){
    
     Std_ReturnType ret_value =E_OK;
    
    if((port > PORT_MAX_NUMBER-1) || (NULL == dir_status))
    {
        ret_value =E_NOT_OK;
    }
    else
    {
        *dir_status = tris_regs[port] ;
    }
    
    return ret_value;
 
}

Std_ReturnType gpio_port_write_logic(Port_Index_t port , uint8 logic){
    
     Std_ReturnType ret_value =E_OK;
    
    if(port > PORT_MAX_NUMBER-1)
    {
        ret_value =E_NOT_OK;
    }
    else
    {
        *lat_regs[port] = logic ;
    }
    
    return ret_value;
}
    


Std_ReturnType gpio_port_read_logic(Port_Index_t port , uint8 *logic){
    
     Std_ReturnType ret_value =E_OK;
    
    if((port > PORT_MAX_NUMBER-1) || (NULL == logic))
    {
        ret_value =E_NOT_OK;
    }
    else
    {
        *logic = lat_regs[port] ;
    }
    
    return ret_value;
    
}

Std_ReturnType gpio_port_toggle(Port_Index_t port){
    
     Std_ReturnType ret_value =E_OK;
    
    if((port > PORT_MAX_NUMBER-1))
    {
        ret_value =E_NOT_OK;
    }
    else
    {
        *lat_regs[port] ^= PORT_MASK;
    }
    
    return ret_value;
}