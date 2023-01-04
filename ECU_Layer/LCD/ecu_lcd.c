/* 
 * File:   ecu_lcd.c
 * Author: walid omar
 *
 * Created on December 14, 2022, 7:10 PM
 */

#include "ecu_lcd.h"

static Std_ReturnType lcd_send_4bit(lcd_4bit_config_t *lcd,uint8 data_command);
static Std_ReturnType lcd_4bit_send_enable_signal(lcd_4bit_config_t *lcd);
static Std_ReturnType lcd_8bit_send_enable_signal(lcd_8bit_config_t *lcd);
static Std_ReturnType lcd_send_8bit(lcd_8bit_config_t *lcd,uint8 data_command);

/******************* LCD 4_BIT MODE INTERFACES ************************/

Std_ReturnType lcd_4bit_init(const lcd_4bit_config_t *lcd){
    Std_ReturnType ret_value=E_OK;
    uint8 counter=0;
    if(NULL == lcd){
        ret_value=E_NOT_OK;
    }
    else
    {
        ret_value=gpio_pin_init(&(lcd->lcd_en));
        ret_value=gpio_pin_init(&(lcd->lcd_rs));
        for(counter=0;counter<4;counter++){
            ret_value=gpio_pin_init(&(lcd->lcd_data[counter]));
        }
        __delay_ms(20);
        ret_value=lcd_4bit_send_command(lcd,_LCD_8BIT_MODE_2_LINES);
        __delay_ms(5);
        ret_value=lcd_4bit_send_command(lcd,_LCD_8BIT_MODE_2_LINES);
        __delay_us(150);
        ret_value=lcd_4bit_send_command(lcd,_LCD_8BIT_MODE_2_LINES);
        
        ret_value=lcd_4bit_send_command(lcd,_LCD_CLEAR);
        ret_value=lcd_4bit_send_command(lcd,_LCD_RETURN_HOME);
        ret_value=lcd_4bit_send_command(lcd,_LCD_ENTRY_MODE_SET_INC_SHIFT_OFF);
        ret_value=lcd_4bit_send_command(lcd,_LCD_DISPLAY_ON_CURSOR_OFF);
        ret_value=lcd_4bit_send_command(lcd,_LCD_4BIT_MODE_2_LINES);
        ret_value=lcd_4bit_send_command(lcd,_LCD_DDRAM_START);
        
    }
    return ret_value;
}

Std_ReturnType lcd_4bit_send_command(const lcd_4bit_config_t *lcd ,uint8 command){
     Std_ReturnType ret_value=E_OK;
    if(NULL == lcd){
        ret_value=E_NOT_OK;
    }
    else
    {
        ret_value=gpio_pin_write_logic(&(lcd->lcd_rs),LOW);
        ret_value=lcd_send_4bit(lcd,command >> 4);
        ret_value=lcd_4bit_send_enable_signal(lcd);
        ret_value= lcd_send_4bit(lcd,command);
        ret_value=lcd_4bit_send_enable_signal(lcd);
    }
    return ret_value;
}

Std_ReturnType lcd_4bit_send_char(const lcd_4bit_config_t *lcd ,uint8 data){
     Std_ReturnType ret_value=E_OK;
    if(NULL == lcd){
        ret_value=E_NOT_OK;
    }
    else
    {
        ret_value=gpio_pin_write_logic(&(lcd->lcd_rs),HIGH);
        ret_value=lcd_send_4bit(lcd,data >> 4);
        ret_value=lcd_4bit_send_enable_signal(lcd);
        ret_value= lcd_send_4bit(lcd,data);
        ret_value=lcd_4bit_send_enable_signal(lcd); 
    }
    return ret_value;
}

Std_ReturnType lcd_4bit_send_char_at_pos(const lcd_4bit_config_t *lcd ,uint8 data,uint8 row,uint8 column){
     Std_ReturnType ret_value=E_OK;
     column--;
    if(NULL == lcd){
        ret_value=E_NOT_OK;
    }
    else
    {
        switch(row){
            case 1: lcd_4bit_send_command(lcd,0x80+column);break;
            case 2: lcd_4bit_send_command(lcd,0xc0+column);break;
            case 3: lcd_4bit_send_command(lcd,0x94+column);break; 
            case 4: lcd_4bit_send_command(lcd,0xd4+column);break;
            default: ;
        }
        lcd_4bit_send_char(lcd,data);
        
    }
    return ret_value;
}

Std_ReturnType lcd_4bit_send_string(const lcd_4bit_config_t *lcd ,uint8 *str){
    Std_ReturnType ret_value=E_OK;
    if(NULL == lcd || NULL == str){
        ret_value=E_NOT_OK;
    }
    else
    {
        while(*str!='\0'){
            ret_value=lcd_4bit_send_char(lcd,*str++);
        }
        
    }
    return ret_value;
}

Std_ReturnType lcd_4bit_send_string_at_pos(const lcd_4bit_config_t *lcd ,uint8 *str,uint8 row,uint8 column){
    Std_ReturnType ret_value=E_OK;
    column--;
    if(NULL == lcd || NULL == str){
        ret_value=E_NOT_OK;
    }
    else
    {
         switch(row){
            case 1 : lcd_4bit_send_command(lcd,(0x80+column)); break;
            case 2 : lcd_4bit_send_command(lcd,(0xc0+column)); break;
            case 3 : lcd_4bit_send_command(lcd,(0x94+column)); break;
            case 4 : lcd_4bit_send_command(lcd,(0xd4+column)); break;
            default : ;
        }
        ret_value=lcd_4bit_send_string(lcd,str);
        
    }
    return ret_value;
}

Std_ReturnType lcd_4bit_send_custom_char(const lcd_4bit_config_t *lcd, uint8 row, uint8 column,const uint8 chr[], uint8 mem_pos){
    Std_ReturnType ret_value=E_OK;
    uint8 counter=0;
    if(NULL == lcd ){
        ret_value=E_NOT_OK;
    }
    else
    {
        ret_value = lcd_4bit_send_command(lcd,(_LCD_CGRAM_START +(mem_pos*8)));
        for(counter=0;counter<8;counter++){
            ret_value = lcd_4bit_send_char(lcd,chr[counter]);
        }
        ret_value = lcd_4bit_send_char_at_pos(lcd,mem_pos,row,column);
        
    }
    return ret_value;
}

/******************* LCD 8_BIT MODE INTERFACES ************************/

Std_ReturnType lcd_8bit_init(const lcd_8bit_config_t *lcd){
     Std_ReturnType ret_value=E_OK;
     uint8 counter=0;
    if(NULL == lcd ){
        ret_value=E_NOT_OK;
    }
    else
    {
         ret_value=gpio_pin_init(&(lcd->lcd_en));
        ret_value=gpio_pin_init(&(lcd->lcd_rs));
        for(counter=0;counter<8;counter++){
            ret_value=gpio_pin_init(&(lcd->lcd_data[counter]));
        }
        __delay_ms(20);
        ret_value=lcd_8bit_send_command(lcd,_LCD_8BIT_MODE_2_LINES);
        __delay_ms(5);
        ret_value=lcd_8bit_send_command(lcd,_LCD_8BIT_MODE_2_LINES);
        __delay_us(150);
        ret_value=lcd_8bit_send_command(lcd,_LCD_8BIT_MODE_2_LINES);
        
        ret_value=lcd_8bit_send_command(lcd,_LCD_CLEAR);
        ret_value=lcd_8bit_send_command(lcd,_LCD_RETURN_HOME);
        ret_value=lcd_8bit_send_command(lcd,_LCD_ENTRY_MODE_SET_INC_SHIFT_OFF);
        ret_value=lcd_8bit_send_command(lcd,_LCD_UNDERLINE_CURSOR_ON);
        ret_value=lcd_8bit_send_command(lcd,_LCD_DDRAM_START);
    }
    return ret_value;
}

Std_ReturnType lcd_8bit_send_command(const lcd_8bit_config_t *lcd ,uint8 command){
     Std_ReturnType ret_value=E_OK;
    if(NULL == lcd ){
        ret_value=E_NOT_OK;
    }
    else
    {
        ret_value=gpio_pin_write_logic(&(lcd->lcd_rs),LOW);
        ret_value=lcd_send_8bit(lcd,command);
        ret_value=lcd_8bit_send_enable_signal(lcd);   
    }
    return ret_value;
}

Std_ReturnType lcd_8bit_send_char(const lcd_8bit_config_t *lcd ,uint8 data){
     Std_ReturnType ret_value=E_OK;
    if(NULL == lcd ){
        ret_value=E_NOT_OK;
    }
    else
    {
        ret_value=gpio_pin_write_logic(&(lcd->lcd_rs),HIGH);
        ret_value=lcd_send_8bit(lcd,data);
        ret_value=lcd_8bit_send_enable_signal(lcd);
    }
    return ret_value;
}

Std_ReturnType lcd_8bit_send_char_at_pos(const lcd_8bit_config_t *lcd ,uint8 data,uint8 row,uint8 column){
     Std_ReturnType ret_value=E_OK;
     column--;
    if(NULL == lcd ){
        ret_value=E_NOT_OK;
    }
    else
    {
        switch(row){
            case 1 : lcd_8bit_send_command(lcd,(0x80+column)); break;
            case 2 : lcd_8bit_send_command(lcd,(0xc0+column)); break;
            case 3 : lcd_8bit_send_command(lcd,(0x94+column)); break;
            case 4 : lcd_8bit_send_command(lcd,(0xd4+column)); break;
            default : ;
        }
        lcd_8bit_send_char(lcd,data);
    }
    return ret_value;
}

Std_ReturnType lcd_8bit_send_string(const lcd_8bit_config_t *lcd ,uint8 *str){
     Std_ReturnType ret_value=E_OK;
    if(NULL == lcd || NULL == str){
        ret_value=E_NOT_OK;
    }
    else
    {
        while(*str!='\0')
        {
            lcd_8bit_send_char(lcd,*str++);
        }
        
    }
    return ret_value;
}

Std_ReturnType lcd_8bit_send_string_at_pos(const lcd_8bit_config_t *lcd ,uint8 *str,uint8 row,uint8 column){
    Std_ReturnType ret_value=E_OK;
    column--;
    if(NULL == lcd || NULL == str){
        ret_value=E_NOT_OK;
    }
    else
    {
        switch(row){
            case 1 : lcd_8bit_send_command(lcd,(0x80+column)); break;
            case 2 : lcd_8bit_send_command(lcd,(0xc0+column)); break;
            case 3 : lcd_8bit_send_command(lcd,(0x94+column)); break;
            case 4 : lcd_8bit_send_command(lcd,(0xd4+column)); break;
            default : ;
        }
        ret_value=lcd_8bit_send_string(lcd,str);
    }
    return ret_value;
}

Std_ReturnType lcd_8bit_send_custom_char(const lcd_8bit_config_t *lcd, uint8 row, uint8 column,const uint8 chr[], uint8 mem_pos){
    Std_ReturnType ret_value=E_OK;
    uint8 counter=0;
    if(NULL == lcd){
        ret_value=E_NOT_OK;
    }
    else
    {
        ret_value = lcd_8bit_send_command(lcd,(_LCD_CGRAM_START+(mem_pos*8)));
        for(counter=0;counter<8;counter++){
            ret_value = lcd_8bit_send_char(lcd,chr[counter]);
        }
        ret_value = lcd_8bit_send_char_at_pos(lcd,mem_pos,row,column);
    }
    return ret_value;
}


/********************** HELPER FUNCTIONS *********************************/

Std_ReturnType convert_uint8_to_string(uint8 value, uint8 *str){
    Std_ReturnType ret_value=E_OK;
    if(NULL == str){
        ret_value=E_NOT_OK;
    }
    else
    {
        memset(str,'\0',4);
        sprintf(str,"%i",value);
    }
    return ret_value;
}

Std_ReturnType convert_uint16_to_string(uint16 value, uint8 *str){
    Std_ReturnType ret_value=E_OK;
    if(NULL == str){
        ret_value=E_NOT_OK;
    }
    else
    {
        memset(str,'\0',6);
        sprintf(str,"%i",value);
        
    }
    return ret_value;
}

Std_ReturnType convert_uint32_to_string(uint32 value, uint8 *str){
    Std_ReturnType ret_value=E_OK;
    if(NULL == str){
        ret_value=E_NOT_OK;
    }
    else
    {
        memset(str,'\0',11);
        sprintf(str,"%i",value);
        
    }
    return ret_value;
}

static Std_ReturnType lcd_send_4bit(lcd_4bit_config_t *lcd,uint8 data_command){
    Std_ReturnType ret_value=E_OK;
    uint8 counter=0;
    if(NULL == lcd)
    {
        ret_value=E_NOT_OK;
    }
    else
    {
        for(counter=0;counter<4;counter++)
        {
            ret_value=gpio_pin_write_logic(&(lcd->lcd_data[counter]),(data_command >> counter) & (uint8)0x01 );
        }
        
    }
    return  ret_value;
    
}

static Std_ReturnType lcd_send_8bit(lcd_8bit_config_t *lcd,uint8 data_command){
    Std_ReturnType ret_value=E_OK;
    uint8 counter=0;
    if(NULL == lcd)
    {
        ret_value=E_NOT_OK;
    }
    else
    {
        for(counter=0;counter<8;counter++)
        {
            ret_value=gpio_pin_write_logic(&(lcd->lcd_data[counter]),(data_command >> counter) & (uint8)0x01 );
        }
        
    }
     return  ret_value;
}

static Std_ReturnType lcd_4bit_send_enable_signal(lcd_4bit_config_t *lcd){
    Std_ReturnType ret_value=E_OK;
    if(NULL==lcd){ret_value=E_NOT_OK;}
    else
    {
        ret_value=gpio_pin_write_logic(&(lcd->lcd_en),HIGH);
        __delay_us(5);
        ret_value=gpio_pin_write_logic(&(lcd->lcd_en),LOW);
    }
    return ret_value;
}

static Std_ReturnType lcd_8bit_send_enable_signal(lcd_8bit_config_t *lcd){
    Std_ReturnType ret_value=E_OK;
    if(NULL==lcd){ret_value=E_NOT_OK;}
    else
    {
        ret_value=gpio_pin_write_logic(&(lcd->lcd_en),HIGH);
        __delay_us(5);
        ret_value=gpio_pin_write_logic(&(lcd->lcd_en),LOW);
    }
    return ret_value;
}