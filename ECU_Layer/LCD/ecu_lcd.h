/* 
 * File:   ecu_lcd.h
 * Author: walid omar
 *
 * Created on December 14, 2022, 7:10 PM
 */

#ifndef ECU_LCD_H
#define	ECU_LCD_H

/* Includes Section */
#include "../../MCAL_Layer/GPIO_Module/hal_gpio.h"

/* Macros Declarations */
#define _LCD_CLEAR                          0x01
#define _LCD_RETURN_HOME                    0x02

#define _LCD_ENTRY_MODE_SET_DEC_SHIFT_OFF   0x04
#define _LCD_ENTRY_MODE_SET_DEC_SHIFT_ON    0x05
#define _LCD_ENTRY_MODE_SET_INC_SHIFT_OFF   0x06
#define _LCD_ENTRY_MODE_SET_INC_SHIFT_ON    0x07

#define _LCD_CURSOR_MOVE_SHIFT_LEFT         0x10
#define _LCD_CURSOR_MOVE_SHIFT_RIGHT        0x14
#define _LCD_DISPLAY_SHIFT_LEFT             0x18
#define _LCD_DISPLAY_SHIFT_RIGHT            0x1C

#define _LCD_DISPLAY_ON_CURSOR_OFF          0x0C
#define _LCD_UNDERLINE_CURSOR_ON            0x0E
#define _LCD_BLOCK_CURSOR_ON                0x0D
#define _LCD_DISPLAY_OFF                    0x08

#define _LCD_4BIT_MODE_2_LINES              0x28
#define _LCD_8BIT_MODE_2_LINES              0x38

#define _LCD_CGRAM_START                    0x40
#define _LCD_DDRAM_START                    0x80

/* Data Types Declarations */

typedef struct {
    Pin_Config_t lcd_rs ;
    Pin_Config_t lcd_en;
    Pin_Config_t lcd_data[4];
}lcd_4bit_config_t;

typedef struct {
    Pin_Config_t lcd_rs ;
    Pin_Config_t lcd_en;
    Pin_Config_t lcd_data[8];
}lcd_8bit_config_t;

/* Functions Declarations */

Std_ReturnType lcd_4bit_init(const lcd_4bit_config_t *lcd);
Std_ReturnType lcd_4bit_send_command(const lcd_4bit_config_t *lcd ,uint8 command);
Std_ReturnType lcd_4bit_send_char(const lcd_4bit_config_t *lcd ,uint8 data);
Std_ReturnType lcd_4bit_send_char_at_pos(const lcd_4bit_config_t *lcd ,uint8 data,uint8 row,uint8 column);
Std_ReturnType lcd_4bit_send_string(const lcd_4bit_config_t *lcd ,uint8 *str);
Std_ReturnType lcd_4bit_send_string_at_pos(const lcd_4bit_config_t *lcd ,uint8 *str,uint8 row,uint8 column);
Std_ReturnType lcd_4bit_send_custom_char(const lcd_4bit_config_t *lcd, uint8 row, uint8 column,const uint8 chr[], uint8 mem_pos);


Std_ReturnType lcd_8bit_init(const lcd_8bit_config_t *lcd);
Std_ReturnType lcd_8bit_send_command(const lcd_8bit_config_t *lcd ,uint8 command);
Std_ReturnType lcd_8bit_send_char(const lcd_8bit_config_t *lcd ,uint8 data);
Std_ReturnType lcd_8bit_send_char_at_pos(const lcd_8bit_config_t *lcd ,uint8 data,uint8 row,uint8 column);
Std_ReturnType lcd_8bit_send_string(const lcd_8bit_config_t *lcd ,uint8 *str);
Std_ReturnType lcd_8bit_send_string_at_pos(const lcd_8bit_config_t *lcd ,uint8 *str,uint8 row,uint8 column);
Std_ReturnType lcd_8bit_send_custom_char(const lcd_8bit_config_t *lcd, uint8 row, uint8 column,const uint8 chr[], uint8 mem_pos);

Std_ReturnType convert_uint8_to_string(uint8 value, uint8 *str);
Std_ReturnType convert_uint16_to_string(uint16 value, uint8 *str);
Std_ReturnType convert_uint32_to_string(uint32 value, uint8 *str);


#endif	/* ECU_LCD_H */

