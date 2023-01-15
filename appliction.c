/* 
 * File:   appliction.c
 * Author: Walid Omar
 *
 * Created on November 13, 2022, 9:08 PM
 */

#include "application.h"
Std_ReturnType ret = E_NOT_OK;
uint16 ret_data = 0;

int main(){
    modules_init();
    ret = EEPROM_WriteData(0x3FF,6);
    ret = EEPROM_ReadData(0x3FF,&ret_data);
    while(1){
        
    }
    return (EXIT_SUCCESS);
}


