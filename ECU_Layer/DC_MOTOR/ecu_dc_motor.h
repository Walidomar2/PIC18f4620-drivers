/* 
 * File:   ecu_dc_motor.h
 * Author: Walid Omar
 *
 * Created on December 2, 2022, 10:10 AM
 */

#ifndef ECU_DC_MOTOR_H
#define	ECU_DC_MOTOR_H

/*Includes Section*/
#include "../../MCAL_Layer/GPIO_Module/hal_gpio.h"

/*Data Types Declaration*/

typedef enum {
    MOTOR_OFF ,
    MOTOR_ON
}motor_status;



typedef struct {
    Pin_Config_t dc_motor[2];
}dc_motor_t;


/* Functions Declarations */

Std_ReturnType dc_motor_init(const dc_motor_t * my_motor);
Std_ReturnType dc_motor_move_forward(const dc_motor_t * my_motor);
Std_ReturnType dc_motor_move_backward(const dc_motor_t * my_motor);
Std_ReturnType dc_motor_off(const dc_motor_t * my_motor);

#endif	/* ECU_DC_MOTOR_H */

