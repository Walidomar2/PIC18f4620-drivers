/* 
 * File:   ecu_seven_segment.h
 * Author: Walid Omar
 *
 * Created on December 6, 2022, 10:38 AM
 */

#ifndef ECU_SEVEN_SEGMENT_H
#define	ECU_SEVEN_SEGMENT_H

/* Includes Section */

#include"../../MCAL_Layer/GPIO_Module/hal_gpio.h"

/*Data Types Declaration*/
typedef enum{
    SEGMENT_COMMON_ANODE,
    SEGMENT_COMMON_CATHODE
            
}segment_type_t;

typedef struct{
    Pin_Config_t segment_pins[4];
    segment_type_t segment_type ;
    
}segment_config_t;

/*Function Declaration*/

Std_ReturnType seven_segment_init(const segment_config_t *my_segment);
Std_ReturnType seven_segment_write_number(const segment_config_t *my_segment ,uint8 number);
        
#endif	/* ECU_SEVEN_SEGMENT_H */

