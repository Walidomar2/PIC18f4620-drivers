/* 
 * File:   EEPROM.h
 * Author: Walid Omar
 *
 * Created on January 15, 2023, 11:18 AM
 */

#ifndef EEPROM_H
#define	EEPROM_H

/* Includes Section */
#include "../mcal_std_types.h"
#include "../proc/pic18f4620.h"
#include "../INTERRUPT/mcal_interrupt_config.h"

/* Macros Declarations */


/* Macros Functions Declarations */
#define EEPGD_CLEAR()           (EECON1bits.EEPGD = 0);
#define EEPGD_SET()             (EECON1bits.EEPGD = 1);
#define CFGS_CLEAR()            (EECON1bits.CFGS = 0);
#define CFGS_SET()              (EECON1bits.CFGS = 1);
#define WRITE_ENABLE()          (EECON1bits.WREN = 1);
#define WRITE_DISABLE()         (EECON1bits.WREN = 0);
#define WRITE_SUCCESS()         (EECON1bits.WRERR = 0);
#define WRITE_NOT_SUCCESS()     (EECON1bits.WRERR = 1);
#define WRITE_INIT()            (EECON1bits.WR = 1);
#define WRITE_COMPLETED()       (EECON1bits.WR = 0);
#define READ_INIT()             (EECON1bits.RD = 1);

/* Data Types Declarations */

/* Functions Declarations */
Std_ReturnType EEPROM_ReadData(uint16 D_add,uint16 *data);
Std_ReturnType EEPROM_WriteData(uint16 D_add,uint16 data); 

#endif	/* EEPROM_H */

