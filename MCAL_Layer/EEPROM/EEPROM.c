/* 
 * File:   EEPROM.h
 * Author: Walid Omar
 *
 * Created on January 15, 2023, 11:18 AM
 */

#include "EEPROM.h"

Std_ReturnType EEPROM_ReadData(uint16 D_add,uint16 *data)
{
    Std_ReturnType ret_value =E_NOT_OK;
    if(NULL == data)
    {
        ret_value =E_NOT_OK;
    }
    else{
        EEADR = (uint8)( D_add&0xFF );
        EEADRH = (uint8)((D_add>>8)&(0x03)); // just need the first two bits in that byte
        EEPGD_CLEAR();
        CFGS_CLEAR();
        READ_INIT();
        NOP();
        NOP();
        *data = EEDATA ;  
        ret_value =E_OK;
    }
    return ret_value;
}

Std_ReturnType EEPROM_WriteData(uint16 D_add,uint16 data)
{
    Std_ReturnType ret_value =E_NOT_OK;
    uint8 Interrupt_Status = INTCONbits.GIE;
    
    EEADR = (uint8)( D_add&0xFF );
    EEADRH = (uint8)((D_add>>8)&(0x03)); // just need the first two bits in that byte
    EEDATA = data;
    EEPGD_CLEAR();
    CFGS_CLEAR();
    WRITE_ENABLE();
    
#if INTERRUPT_FEATURE == INTERRUPT_PRIORITY_ENABLE
    GLOBAL_INTE_HIGH_DISABLE();
    GLOBAL_INTE_LOW_DISABLE();
#else
    GLOBAL_INTERRUPT_DISABLE();
#endif 
    
    EECON2 = 0x55;
    EECON2 = 0xAA;
    WRITE_INIT();
    while(EECON1bits.WR);
    if(0 == EECON1bits.WRERR)
    {
        ret_value =E_OK;
    }
    WRITE_DISABLE();
    INTCONbits.GIE = Interrupt_Status;
    return ret_value;
}

