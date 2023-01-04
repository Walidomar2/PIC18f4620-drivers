/* 
 * File:   ecu_keypad.c
 * Author: Walid Omar
 *
 * Created on December 11, 2022, 11:35 PM
 */

#include "ecu_keypad.h"

static const uint8 keypad_values[KEYPAD_ROWS][KEYPAD_COLUMNS] = {
                                            {'7','8','9','/'},
                                            {'4','5','6','*'},
                                            {'1','2','3','-'},
                                            {'#','0','=','+'}};

Std_ReturnType keypad_init(const keypad_config_t *my_keypad){
    Std_ReturnType ret_value =E_OK;
    uint8 rows_counter=0 , columns_counter=0;
    if(NULL==my_keypad)
    {
        ret_value =E_NOT_OK;
    }
    else
    {
        for(rows_counter=0;rows_counter<KEYPAD_ROWS;rows_counter++)
        {
            ret_value=gpio_pin_init(&(my_keypad->keypad_rows[rows_counter]));
        }
         for(columns_counter=0;columns_counter<KEYPAD_COLUMNS;columns_counter++)
        {
            ret_value=gpio_pin_init(&(my_keypad->keypad_columns[columns_counter]));
        }
        ret_value =E_OK;
   
    }
    return ret_value;
}


Std_ReturnType keypad_read(const keypad_config_t *my_keypad,uint8 *value){
     Std_ReturnType ret_value =E_OK;
      uint8 rows_counter=0 , columns_counter=0 ,counter=0;
      Logic_t val;
    if(NULL == my_keypad || NULL == value)
    {
        ret_value =E_NOT_OK;
    }
    else
    {
        for(rows_counter=0;rows_counter<KEYPAD_ROWS;rows_counter++)
        {
            for(counter=0;counter<KEYPAD_ROWS;counter++)
              {
                 ret_value=gpio_pin_write_logic(&(my_keypad->keypad_rows[counter]),LOW);
              }
            ret_value=gpio_pin_write_logic(&(my_keypad->keypad_rows[rows_counter]),HIGH);
             for(columns_counter=0;columns_counter<KEYPAD_COLUMNS;columns_counter++)
              {
                 ret_value=gpio_pin_read_logic(&(my_keypad->keypad_columns[columns_counter]),&val);
                 if(val == HIGH)
                 { 
                   *value = keypad_values[rows_counter][columns_counter];
                   flag = 1; // Global flag to indicate that keypad is pressed 
                 }
              }
        }
        
    }
    return ret_value;
}