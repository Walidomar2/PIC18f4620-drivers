/* 
 * File:   ADC.c
 * Author: Walid Omar
 *
 * Created on January 18, 2023, 8:18 PM
 */

#include "ADC.h"

static Std_ReturnType Result_Format_Config(const adc_config_t *object);
static Std_ReturnType Pin_Config(const adc_config_t *object);
static Std_ReturnType Volt_Reference_Config(const adc_config_t *object);

Std_ReturnType ADC_Init(const adc_config_t *object){
    Std_ReturnType ret_value = E_NOT_OK;
    if(NULL==object)
    {
        ret_value = E_NOT_OK;
    }
    else
    {
        ADC_DISABLE();
        ADCON2bits.ACQT = object->acqu_time ;
        ADCON2bits.ADCS = object->clk_select;
        Pin_Config(object);
        Volt_Reference_Config(object);
        Result_Format_Config(object);
        ADC_ENABLE();
        ret_value = E_OK;
    }
    return ret_value;
}

Std_ReturnType ADC_Deinit(const adc_config_t *object){
    Std_ReturnType ret_value = E_NOT_OK;
    if(NULL==object)
    {
        ret_value = E_NOT_OK;
    }
    else
    {
        ADC_DISABLE();
        ret_value=E_OK;
    }
    return ret_value;
}

Std_ReturnType ADC_StartConversion(const adc_config_t *object){
    Std_ReturnType ret_value = E_NOT_OK;
    if(NULL==object)
    {
        ret_value = E_NOT_OK;
    }
    else
    {
        ADC_CONVERTION_START();
        ret_value = E_OK;
    }
    return ret_value;
}

Std_ReturnType ADC_ConversionStatus(const adc_config_t *object, uint8 *status){
    Std_ReturnType ret_value = E_NOT_OK;
    if((NULL == object) || (NULL == status))
    {
        ret_value = E_NOT_OK;
    }
    else
    {
        *status =(uint8)(!ADC_CONVERTION_STATUS());  // IF THE STATUS IS TRUE (1) SO CONVERSION IS DONE 
        ret_value = E_OK;
    }
    return ret_value;
}

Std_ReturnType ADC_ResultRead(const adc_config_t *object, uint16 *result){
    Std_ReturnType ret_value = E_NOT_OK;
    if((NULL == object) || (NULL == result))
    {
        ret_value = E_NOT_OK;
    }
    else
    {
        ret_value = ADC_StartConversion(object);
        while(ADC_CONVERTION_STATUS());         //WAIT TILL CONVERSION IS DONE
        if( ADC_RIGHT_RESULT == object->res_format)
        {
            *result = (uint16)((ADRESH << 8) + ADRESL);
            ret_value = E_OK;  
        }
        else if(ADC_LEFT_RESULT == object->res_format )
        {
            *result = (uint16)(((ADRESH << 8) + ADRESL) >> 6);
            ret_value = E_OK;
        }
        else
        {
            *result = (uint16)((ADRESH << 8) + ADRESL);
            ret_value = E_OK;  
        }
    }
    return ret_value;
}

Std_ReturnType ADC_ChangeChannel(adc_config_t *object , ADC_channel_select new_channel){
    Std_ReturnType ret_value = E_NOT_OK;
    if(NULL == object)
    {
        ret_value = E_NOT_OK;
    }
    else
    {
        object->channel = new_channel;
        ADCON0bits.CHS = new_channel;
        Pin_Config(object);
    }
    return ret_value;
}

/* ---------------------- Helper Functions -----------------------------------*/

static Std_ReturnType Result_Format_Config(const adc_config_t *object){
    Std_ReturnType ret_value=E_NOT_OK;
    if(NULL == object)
    {
        ret_value=E_NOT_OK;
    }
    else
    {
        if( ADC_RIGHT_RESULT == object->res_format )
        {
            ADC_RES_FORMAT_RIGHT_JUSTIFIED();
            
            ret_value=E_OK;
        }
        else if( ADC_LEFT_RESULT == object->res_format )
        {
            ADC_RES_FORMAT_LEFT_JUSTIFIED();
            ret_value=E_OK;
        }
        else
        { 
            ADC_RES_FORMAT_RIGHT_JUSTIFIED();
            ret_value=E_OK;
        }
    }
    return ret_value;
}

static Std_ReturnType Pin_Config(const adc_config_t *object){
    Std_ReturnType ret_value=E_NOT_OK;
    if(NULL == object)
    {
        ret_value=E_NOT_OK;
    }
    else
    {
        switch(object->channel){
                case ADC_CHANNEL_AN0 :
                    SET_BIT(TRISA,_TRISA_RA0_POSN);
                    ret_value=E_OK;
                    break;
                case ADC_CHANNEL_AN1 :
                    SET_BIT(TRISA,_TRISA_RA1_POSN);
                    ret_value=E_OK;
                    break;
                case ADC_CHANNEL_AN2 :
                    SET_BIT(TRISA,_TRISA_RA2_POSN);
                    ret_value=E_OK;
                    break;
                case ADC_CHANNEL_AN3 :
                    SET_BIT(TRISA,_TRISA_RA3_POSN);
                    ret_value=E_OK;
                    break;
                case ADC_CHANNEL_AN4 :
                    SET_BIT(TRISA,_TRISA_RA5_POSN);
                    ret_value=E_OK;
                    break;
                case ADC_CHANNEL_AN5 :
                    SET_BIT(TRISE,_TRISE_RE0_POSN);
                    ret_value=E_OK;
                    break;
                case ADC_CHANNEL_AN6 :
                    SET_BIT(TRISE,_TRISE_RE1_POSN);
                    ret_value=E_OK;
                    break;
                case ADC_CHANNEL_AN7 :
                    SET_BIT(TRISE,_TRISE_RE2_POSN);
                    ret_value=E_OK;
                    break;
                case ADC_CHANNEL_AN8 :
                    SET_BIT(TRISB,_TRISB_RB2_POSN);
                    ret_value=E_OK;
                    break;
                case ADC_CHANNEL_AN9 :
                    SET_BIT(TRISB,_TRISB_RB3_POSN);
                    ret_value=E_OK;
                    break;
                case ADC_CHANNEL_AN10 :
                    SET_BIT(TRISB,_TRISB_RB1_POSN);
                    ret_value=E_OK;
                    break;
                case ADC_CHANNEL_AN11 :
                    SET_BIT(TRISB,_TRISB_RB4_POSN);
                    ret_value=E_OK;
                    break;
                case ADC_CHANNEL_AN12 :
                    SET_BIT(TRISB,_TRISB_RB0_POSN);
                    ret_value=E_OK;
                    break;
                default :
                    ret_value=E_NOT_OK; 
        }
    }
    return ret_value;
}

static Std_ReturnType Volt_Reference_Config(const adc_config_t *object){
    Std_ReturnType ret_value=E_NOT_OK;
    if(NULL == object)
    {
        ret_value=E_NOT_OK;
    }
    else
    {
        if(ADC_VOLTAGE_REFERENCE_ENABLE == object->volt_sou_sel)
        {
           ADC_ENABLE_VOLTAGE_REFERENCE();
           ret_value=E_OK;
        }
        else if(ADC_VOLTAGE_REFERENCE_DISABLE == object->volt_sou_sel)
        {
            ADC_DISABLE_VOLTAGE_REFERENCE();
            ret_value=E_OK;
        }
        else
        {
            ADC_DISABLE_VOLTAGE_REFERENCE();
            ret_value=E_OK;
        }
    }
    return ret_value;
}