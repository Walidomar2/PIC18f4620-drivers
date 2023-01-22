/* 
 * File:   ADC.h
 * Author: Walid Omar
 *
 * Created on January 18, 2023, 8:18 PM
 */

#ifndef ADC_H
#define	ADC_H

/* Includes Sections */
#include "../GPIO_Module/hal_gpio.h"
#include "../INTERRUPT/mcal_internal_interrupt.h"

/* Macros Declarations */

// SELECTED PINS START FROM AN0 
#define ADC_SELECT_ALL_PINS_ANALOG         0x00
#define ADC_SELECT_ALL_PINS_DIGITAL        0x00
#define ADC_SELECT_12PINS_ANALOG           0x03
#define ADC_SELECT_11PINS_ANALOG           0x04
#define ADC_SELECT_10PINS_ANALOG           0x05
#define ADC_SELECT_9PINS_ANALOG            0x06
#define ADC_SELECT_8PINS_ANALOG            0x07
#define ADC_SELECT_7PINS_ANALOG            0x08
#define ADC_SELECT_6PINS_ANALOG            0x09
#define ADC_SELECT_5PINS_ANALOG            0x0A
#define ADC_SELECT_4PINS_ANALOG            0x0B
#define ADC_SELECT_3PINS_ANALOG            0x0C
#define ADC_SELECT_2PINS_ANALOG            0x0D
#define ADC_SELECT_1PINS_ANALOG            0x0E

/* Macro Functions Declarations */
#define ADC_ENABLE()            (ADCON0bits.ADON = 1 )
#define ADC_DISABLE()           (ADCON0bits.ADON = 0 )
#define ADC_CONVERTION_START()  (ADCON0bits.GODONE = 1)
#define ADC_CONVERTION_STATUS()  (ADCON0bits.GODONE)

#define ADC_ANALOG_DIGITAL_PORT_CONFIG(_config)         (ADCON1bits.PCFG = _config) //SELECTED HOW MANY ANALOG PINS YOU NEED

#define ADC_ENABLE_VOLTAGE_REFERENCE()              do{ADCON1bits.VCFG0 = 1;\
                                                       ADCON1bits.VCFG1 = 1;\
                                                     }while(0)
                                                                 
#define ADC_DISABLE_VOLTAGE_REFERENCE()              do{ADCON1bits.VCFG0 = 0;\
                                                        ADCON1bits.VCFG1 = 0;\
                                                     }while(0)

#define ADC_RES_FORMAT_RIGHT_JUSTIFIED()            ( ADCON2bits.ADFM = 1)

#define ADC_RES_FORMAT_LEFT_JUSTIFIED()             ( ADCON2bits.ADFM = 0)                                                     



/* Data Types Declarations */

typedef enum{
    ADC_CHANNEL_AN0 =0,
    ADC_CHANNEL_AN1,
    ADC_CHANNEL_AN2,
    ADC_CHANNEL_AN3,  
    ADC_CHANNEL_AN4,
    ADC_CHANNEL_AN5,
    ADC_CHANNEL_AN6,
    ADC_CHANNEL_AN7,
    ADC_CHANNEL_AN8,
    ADC_CHANNEL_AN9,
    ADC_CHANNEL_AN10,
    ADC_CHANNEL_AN11,
    ADC_CHANNEL_AN12        
}ADC_channel_select; 

typedef enum{
    ADC_0_TAD = 0,
    ADC_2_TAD,
    ADC_4_TAD,
    ADC_6_TAD,
    ADC_8_TAD,
    ADC_12_TAD,
    ADC_16_TAD,
    ADC_20_TAD
}ADC_acquisition_time_select;

typedef enum{
    ADC_FOSC_DIV_2 = 0,
    ADC_FOSC_DIV_8,
    ADC_FOSC_DIV_32,
    ADC_FRC,
    ADC_FOSC_DIV_4,
    ADC_FOSC_DIV_16,
    ADC_FOSC_DIV_64
}ADC_clock_select;

typedef enum{
    ADC_VOLTAGE_REFERENCE_DISABLE = 0,
    ADC_VOLTAGE_REFERENCE_ENABLE = 1,        
}ADC_volt_ref;

typedef enum{
    ADC_LEFT_RESULT   = 0,
    ADC_RIGHT_RESULT  = 1,        
}ADC_result_format;

typedef struct{
#if ADC_INTERRUPT_FEATURE  == INTERRUPT_FEATURE_ENABLE
    void(*ADC_InterruptHandler)(void);
    interrupt_priority  priority;
#endif
    ADC_channel_select            channel;
    ADC_acquisition_time_select   acqu_time;
    ADC_clock_select              clk_select;
    ADC_volt_ref                  volt_sou_sel;
    ADC_result_format             res_format;
}adc_config_t;


/* Functions Declarations */

Std_ReturnType ADC_Init(const adc_config_t *object);
Std_ReturnType ADC_Deinit(const adc_config_t *object);
Std_ReturnType ADC_StartConversion(const adc_config_t *object);
Std_ReturnType ADC_GetConversion(const adc_config_t *object);
Std_ReturnType ADC_ConversionStatus(const adc_config_t *object, uint8 *status);
Std_ReturnType ADC_ResultRead(const adc_config_t *object, uint16 *result);
Std_ReturnType ADC_ChangeChannel( adc_config_t *object , ADC_channel_select new_channel);




#endif	/* ADC_H */

