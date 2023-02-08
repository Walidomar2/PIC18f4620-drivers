/* 
 * File:   mcal_internal_interrupt.c
 * Author: Walid Omar
 *
 * Created on December 31, 2022, 9:23 PM
 */

#include "mcal_internal_interrupt.h"
static void(*ADC_InterruptHandler)(void) = NULL;
static void(*TMR0_InterruptHandler)(void) = NULL;
static void(*TMR1_InterruptHandler)(void) = NULL;
static void(*TMR2_InterruptHandler)(void) = NULL;
static void(*TMR3_InterruptHandler)(void) = NULL;
static void(*EUSART_TX_InterruptHandler)(void) = NULL;
static void(*EUSART_RX_InterruptHandler)(void) = NULL;
static void(*I2C_InterruptHandler)(void) = NULL;
static void(*I2C_BC_InterruptHandler)(void) = NULL;
static void(*SPI_InterruptHandler)(void) = NULL;
static void(*CCP1_InterruptHandler)(void) = NULL;
static void(*CCP2_InterruptHandler)(void) = NULL;
static volatile uint16 TMR0_preload_value = 0;
static volatile uint16 TMR1_preload_value = 0;
/*----------------------------------------------- ADC FUNCTIONS -------------------------------------------------------*/
Std_ReturnType Interrupt_ADC_Enable(const interrupt_ADC_t *object){
    Std_ReturnType ret_value =E_NOT_OK;
    if(NULL == object)
    {
        ret_value =E_NOT_OK;
    }
    else
    {
        ADC_INTERRUPT_DISABLE();
#if INTERRUPT_FEATURE == INTERRUPT_PRIORITY_ENABLE
        if(HIGH_PRIORITY == object->periority)
        {
            GLOBAL_INTE_HIGH_ENABLE();  
            ADC_INTERRUPT_HIGH_PRIORITY();
        }
        else if(LOW_PRIORITY == object->periority)
        {
            GLOBAL_INTE_LOW_ENABLE();
            ADC_INTERRUPT_LOW_PRIORITY();
        }
        else{/* Nothing */}
#else
        GLOBAL_INTERRUPT_ENABLE();
        PERIPHERAL_INTERRUPT_ENABLE();
#endif
        ADC_InterruptHandler = object->ADC_ExceptionHandler;
        ADC_INTERRUPT_ENABLE();
        ret_value=E_OK;
    }
    return ret_value;
}
Std_ReturnType Interrupt_ADC_Disable(const interrupt_ADC_t *object){
      Std_ReturnType ret_value =E_NOT_OK;
    if(NULL == object)
    {
        ret_value =E_NOT_OK;
    }
    else
    {
        ADC_INTERRUPT_DISABLE();
        return ret_value;
    }
    return ret_value;
}

/*----------------------------------------------- TMR0 FUNCTIONS -------------------------------------------------------*/
Std_ReturnType Interrupt_TMR0_Enable(const interrupt_TMR0_t *object){
      Std_ReturnType ret_value =E_NOT_OK;
    if(NULL == object)
    {
        ret_value =E_NOT_OK;
    }
    else
    {
        TMR0_INTERRUPT_DISABLE();
#if INTERRUPT_FEATURE == INTERRUPT_PRIORITY_ENABLE
        if(HIGH_PRIORITY == object->periority)
        {
            GLOBAL_INTE_HIGH_ENABLE();  
            TMR0_INTERRUPT_HIGH_PRIORITY();
        }
        else if(LOW_PRIORITY == object->periority)
        {
            GLOBAL_INTE_LOW_ENABLE();
            TMR0_INTERRUPT_LOW_PRIORITY();
        }
        else{/* Nothing */}
#else
        GLOBAL_INTERRUPT_ENABLE();
        PERIPHERAL_INTERRUPT_ENABLE();
#endif
        TMR0_InterruptHandler = object->TMR0_ExceptionHandler;
        TMR0H = (object->preload_value) >> 8;
        TMR0L = (uint8)(object->preload_value);
        TMR0_preload_value = object->preload_value;
        TMR0_INTERRUPT_ENABLE();
        ret_value=E_OK;
    }
    return ret_value;
}
Std_ReturnType Interrupt_TMR0_Disable(const interrupt_TMR0_t *object){
      Std_ReturnType ret_value =E_NOT_OK;
    if(NULL == object)
    {
        ret_value =E_NOT_OK;
    }
    else
    {
        TMR0_INTERRUPT_DISABLE();
        ret_value=E_OK;
    }
    return ret_value;
}

/*----------------------------------------------- TMR1 FUNCTIONS -------------------------------------------------------*/
Std_ReturnType Interrupt_TMR1_Enable(const interrupt_TMR1_t *object){
      Std_ReturnType ret_value =E_NOT_OK;
    if(NULL == object)
    {
        ret_value =E_NOT_OK;
    }
    else
    {
        TMR1_INTERRUPT_DISABLE();
#if INTERRUPT_FEATURE == INTERRUPT_PRIORITY_ENABLE
        if(HIGH_PRIORITY == object->periority)
        {
            GLOBAL_INTE_HIGH_ENABLE();  
            TMR1_INTERRUPT_HIGH_PRIORITY();
        }
        else if(LOW_PRIORITY == object->periority)
        {
            GLOBAL_INTE_LOW_ENABLE();
            TMR1_INTERRUPT_LOW_PRIORITY();
        }
        else{/* Nothing */}
#else
        GLOBAL_INTERRUPT_ENABLE();
        PERIPHERAL_INTERRUPT_ENABLE();
#endif
        TMR1_InterruptHandler = object->TMR1_ExceptionHandler;
        TMR1_preload_value = object->preload_value;
        TMR1_INTERRUPT_ENABLE();
        ret_value=E_OK;
    }
      return ret_value;
}
Std_ReturnType Interrupt_TMR1_Disable(const interrupt_TMR1_t *object){
      Std_ReturnType ret_value =E_NOT_OK;
    if(NULL == object)
    {
        ret_value =E_NOT_OK;
    }
    else
    {
        TMR1_INTERRUPT_DISABLE();
        ret_value=E_OK;
    }
    return ret_value;
}

/*----------------------------------------------- TMR2 FUNCTIONS -------------------------------------------------------*/
Std_ReturnType Interrupt_TMR2_Enable(const interrupt_TMR2_t *object){
      Std_ReturnType ret_value =E_NOT_OK;
    if(NULL == object)
    {
        ret_value =E_NOT_OK;
    }
    else
    {
        TMR2_INTERRUPT_DISABLE();
#if INTERRUPT_FEATURE == INTERRUPT_PRIORITY_ENABLE
        if(HIGH_PRIORITY == object->periority)
        {
            GLOBAL_INTE_HIGH_ENABLE();  
            TMR2_INTERRUPT_HIGH_PRIORITY();
        }
        else if(LOW_PRIORITY == object->periority)
        {
            GLOBAL_INTE_LOW_ENABLE();
            TMR2_INTERRUPT_LOW_PRIORITY();
        }
        else{/* Nothing */}
#else
        GLOBAL_INTERRUPT_ENABLE();
        PERIPHERAL_INTERRUPT_ENABLE();
#endif
        TMR2_InterruptHandler = object->TMR2_ExceptionHandler;
        TMR2_INTERRUPT_ENABLE();
        ret_value=E_OK;
    }
    return ret_value;
}
Std_ReturnType Interrupt_TMR2_Disable(const interrupt_TMR2_t *object){
      Std_ReturnType ret_value =E_NOT_OK;
    if(NULL == object)
    {
        ret_value =E_NOT_OK;
    }
    else
    {
        TMR2_INTERRUPT_DISABLE();
        ret_value =E_OK;
    }
    return ret_value;
}

/*----------------------------------------------- TMR3 FUNCTIONS -------------------------------------------------------*/
Std_ReturnType Interrupt_TMR3_Enable(const interrupt_TMR3_t *object){
      Std_ReturnType ret_value =E_NOT_OK;
    if(NULL == object)
    {
        ret_value =E_NOT_OK;
    }
    else
    {
        TMR3_INTERRUPT_DISABLE();
#if INTERRUPT_FEATURE == INTERRUPT_PRIORITY_ENABLE
        if(HIGH_PRIORITY == object->periority)
        {
            GLOBAL_INTE_HIGH_ENABLE();  
            TMR3_INTERRUPT_HIGH_PRIORITY();
        }
        else if(LOW_PRIORITY == object->periority)
        {
            GLOBAL_INTE_LOW_ENABLE();
            TMR3_INTERRUPT_LOW_PRIORITY();
        }
        else{/* Nothing */}
#else
        GLOBAL_INTERRUPT_ENABLE();
        PERIPHERAL_INTERRUPT_ENABLE();
#endif
        TMR3_InterruptHandler = object->TMR3_ExceptionHandler;
        TMR3_INTERRUPT_ENABLE();
        ret_value=E_OK;
    }
    return ret_value;
}
Std_ReturnType Interrupt_TMR3_Disable(const interrupt_TMR3_t *object){
      Std_ReturnType ret_value =E_NOT_OK;
    if(NULL == object)
    {
        ret_value =E_NOT_OK;
    }
    else
    {
        TMR3_INTERRUPT_DISABLE();
        ret_value = E_OK;
    }
    return ret_value;
}

/*----------------------------------------------- EUSART_TX FUNCTIONS ---------------------------------------------------*/
Std_ReturnType Interrupt_EUSART_TX_Enable(const interrupt_EUSART_TX_t *object){
      Std_ReturnType ret_value =E_NOT_OK;
    if(NULL == object)
    {
        ret_value =E_NOT_OK;
    }
    else
    {
        EUSART_TX_INTERRUPT_DISABLE();
#if INTERRUPT_FEATURE == INTERRUPT_PRIORITY_ENABLE
        if(HIGH_PRIORITY == object->periority)
        {
           GLOBAL_INTE_HIGH_ENABLE();  
           EUSART_TX_INTERRUPT_HIGH_PRIORITY();
        }
        else if(LOW_PRIORITY == object->periority)
        {
           GLOBAL_INTE_LOW_ENABLE();
           EUSART_TX_INTERRUPT_LOW_PRIORITY();
        }
        else{/* Nothing */}
#else
        GLOBAL_INTERRUPT_ENABLE();
        PERIPHERAL_INTERRUPT_ENABLE();
#endif
        EUSART_TX_InterruptHandler= object->EUSART_TX_ExceptionHandler;
        EUSART_TX_INTERRUPT_ENABLE();
        ret_value=E_OK;
    }
    return ret_value;
}
Std_ReturnType Interrupt_EUSART_TX_Disable(const interrupt_EUSART_TX_t *object){
      Std_ReturnType ret_value =E_NOT_OK;
    if(NULL == object)
    {
        ret_value =E_NOT_OK;
    }
    else
    {
        EUSART_TX_INTERRUPT_DISABLE();
        ret_value = E_OK;
    }
    return ret_value;
}

/*----------------------------------------------- EUSART_RX FUNCTIONS ---------------------------------------------------*/
Std_ReturnType Interrupt_EUSART_RX_Enable(const interrupt_EUSART_RX_t *object){
      Std_ReturnType ret_value =E_NOT_OK;
    if(NULL == object)
    {
        ret_value =E_NOT_OK;
    }
    else
    {
         EUSART_RX_INTERRUPT_DISABLE();
#if INTERRUPT_FEATURE == INTERRUPT_PRIORITY_ENABLE
        if(HIGH_PRIORITY == object->periority)
        {
           GLOBAL_INTE_HIGH_ENABLE();  
           EUSART_RX_INTERRUPT_HIGH_PRIORITY();
        }
        else if(LOW_PRIORITY == object->periority)
        {
           GLOBAL_INTE_LOW_ENABLE();
           EUSART_RX_INTERRUPT_LOW_PRIORITY();
        }
        else{/* Nothing */}
#else
        GLOBAL_INTERRUPT_ENABLE();
        PERIPHERAL_INTERRUPT_ENABLE();
#endif
        EUSART_RX_InterruptHandler= object->EUSART_RX_ExceptionHandler;
        EUSART_RX_INTERRUPT_ENABLE();
        ret_value=E_OK;
    }
    return ret_value;
}
Std_ReturnType Interrupt_EUSART_RX_Disable(const interrupt_EUSART_RX_t *object){
      Std_ReturnType ret_value =E_NOT_OK;
    if(NULL == object)
    {
        ret_value =E_NOT_OK;
    }
    else
    {
        EUSART_RX_INTERRUPT_DISABLE();
        ret_value =E_OK;
    }
    return ret_value;
}

/*----------------------------------------------- I2C FUNCTIONS ---------------------------------------------------------*/
Std_ReturnType Interrupt_I2C_Enable(const interrupt_I2C_t *object){
      Std_ReturnType ret_value =E_NOT_OK;
    if(NULL == object)
    {
        ret_value =E_NOT_OK;
    }
    else
    {
        I2C_INTERRUPT_DISABLE();
        I2C_BUS_COL_DISABLE();
#if INTERRUPT_FEATURE == INTERRUPT_PRIORITY_ENABLE
        if(HIGH_PRIORITY == object->periority)
        {
            GLOBAL_INTE_HIGH_ENABLE();  
            I2C_INTERRUPT_HIGH_PRIORITY();
            I2C_BUS_COL_HIGH_PRIORITY();
        }
        else if(LOW_PRIORITY == object->periority)
        {
            GLOBAL_INTE_LOW_ENABLE();
            I2C_INTERRUPT_LOW_PRIORITY();
            I2C_BUS_COL_LOW_PRIORITY();
        }
        else{/* Nothing */}
#else
        GLOBAL_INTERRUPT_ENABLE();
        PERIPHERAL_INTERRUPT_ENABLE();
#endif
        I2C_InterruptHandler = object->I2C_ExceptionHandler;
        I2C_BC_InterruptHandler = object->BC_ExceptionHandler;
        I2C_INTERRUPT_ENABLE();
        I2C_BUS_COL_ENABLE();
        ret_value=E_OK;
    }
    return ret_value;
}
Std_ReturnType Interrupt_I2C_Disable(const interrupt_I2C_t *object){
      Std_ReturnType ret_value =E_NOT_OK;
    if(NULL == object)
    {
        ret_value =E_NOT_OK;
    }
    else
    {
        I2C_INTERRUPT_DISABLE();
        I2C_BUS_COL_DISABLE();
        ret_value =E_OK;
    }
    return ret_value;
}

/*----------------------------------------------- SPI FUNCTIONS ---------------------------------------------------------*/
Std_ReturnType Interrupt_SPI_Enable(const interrupt_SPI_t *object){
      Std_ReturnType ret_value =E_NOT_OK;
    if(NULL == object)
    {
        ret_value =E_NOT_OK;
    }
    else
    {
        
        SPI_INTERRUPT_DISABLE();
#if INTERRUPT_FEATURE == INTERRUPT_PRIORITY_ENABLE
        if(HIGH_PRIORITY == object->periority)
        {
            GLOBAL_INTE_HIGH_ENABLE();  
            SPI_INTERRUPT_HIGH_PRIORITY();
        }
        else if(LOW_PRIORITY == object->periority)
        {
            GLOBAL_INTE_LOW_ENABLE();
            SPI_INTERRUPT_LOW_PRIORITY();
        }
        else{/* Nothing */}
#else
        GLOBAL_INTERRUPT_ENABLE();
        PERIPHERAL_INTERRUPT_ENABLE();
#endif
        SPI_InterruptHandler = object->SPI_ExceptionHandler;
        SPI_INTERRUPT_ENABLE();
        ret_value=E_OK;
    }
    return ret_value;
}
Std_ReturnType Interrupt_SPI_Disable(const interrupt_SPI_t *object){
      Std_ReturnType ret_value =E_NOT_OK;
    if(NULL == object)
    {
        ret_value =E_NOT_OK;
    }
    else
    {
        SPI_INTERRUPT_DISABLE();
        ret_value=E_OK;
    }
    return ret_value;
}

/*----------------------------------------------- CCP1 FUNCTIONS ---------------------------------------------------------*/
Std_ReturnType Interrupt_CCP1_Enable(const interrupt_CCP1_t *object){
      Std_ReturnType ret_value =E_NOT_OK;
    if(NULL == object)
    {
        ret_value =E_NOT_OK;
    }
    else
    {
        CCP1_INTERRUPT_DISABLE();
#if INTERRUPT_FEATURE == INTERRUPT_PRIORITY_ENABLE
        if(HIGH_PRIORITY == object->periority)
        {
            GLOBAL_INTE_HIGH_ENABLE();  
            CCP1_INTERRUPT_HIGH_PRIORITY();
        }
        else if(LOW_PRIORITY == object->periority)
        {
            GLOBAL_INTE_LOW_ENABLE();
            CCP1_INTERRUPT_LOW_PRIORITY();
        }
        else{/* Nothing */}
#else
        GLOBAL_INTERRUPT_ENABLE();
        PERIPHERAL_INTERRUPT_ENABLE();
#endif
        CCP1_InterruptHandler = object->CCP1_ExceptionHandler;
        CCP1_INTERRUPT_ENABLE();
        ret_value=E_OK;
    }
    return ret_value;
}
Std_ReturnType Interrupt_CCP1_Disable(const interrupt_CCP1_t *object){
      Std_ReturnType ret_value =E_NOT_OK;
    if(NULL == object)
    {
        ret_value =E_NOT_OK;
    }
    else
    {
        CCP1_INTERRUPT_DISABLE();
        ret_value=E_OK;
    }
    return ret_value;
}

/*----------------------------------------------- CCP2 FUNCTIONS ---------------------------------------------------------*/
Std_ReturnType Interrupt_CCP2_Enable(const interrupt_CCP2_t *object){
      Std_ReturnType ret_value =E_NOT_OK;
    if(NULL == object)
    {
        ret_value =E_NOT_OK;
    }
    else
    {
        CCP2_INTERRUPT_DISABLE();
#if INTERRUPT_FEATURE == INTERRUPT_PRIORITY_ENABLE
        if(HIGH_PRIORITY == object->periority)
        {
            GLOBAL_INTE_HIGH_ENABLE();  
            CCP2_INTERRUPT_HIGH_PRIORITY();
        }
        else if(LOW_PRIORITY == object->periority)
        {
            GLOBAL_INTE_LOW_ENABLE();
            CCP2_INTERRUPT_LOW_PRIORITY();
        }
        else{/* Nothing */}
#else
        GLOBAL_INTERRUPT_ENABLE();
        PERIPHERAL_INTERRUPT_ENABLE();
#endif
        CCP2_InterruptHandler = object->CCP2_ExceptionHandler;
        CCP2_INTERRUPT_ENABLE();
        ret_value=E_OK;
    }
    return ret_value;
}
Std_ReturnType Interrupt_CCP2_Disable(const interrupt_CCP2_t *object){
      Std_ReturnType ret_value =E_NOT_OK;
    if(NULL == object)
    {
        ret_value =E_NOT_OK;
    }
    else
    {
        CCP2_INTERRUPT_DISABLE();
        ret_value=E_OK;
    }
    return ret_value;
}

/*--------------------------- ISR Functions -------------------------- */
void ADC_ISR(void){
    ADC_INTERRUPT_CLEAR_FLAG();
    if(ADC_InterruptHandler)
    {
        ADC_InterruptHandler();
    }
}

void TMR0_ISR(void){
    TMR0_INTERRUPT_CLEAR_FLAG();
    TMR0H = (TMR0_preload_value ) >> 8;
    TMR0L = (uint8)(TMR0_preload_value) ;
    if(TMR0_InterruptHandler)
    {
        TMR0_InterruptHandler();
    }
}

void TMR1_ISR(void)
{
    TMR1_INTERRUPT_CLEAR_FLAG();
    TMR1H = (TMR1_preload_value ) >> 8;
    TMR1L = (uint8)(TMR1_preload_value) ;
    if(TMR1_InterruptHandler)
    {
        TMR1_InterruptHandler();
    }
}

void TMR2_ISR(void)
{
    TMR2_INTERRUPT_CLEAR_FLAG();
    if(TMR2_InterruptHandler)
    {
        TMR2_InterruptHandler();
    }
 }

void TMR3_ISR(void)
{
    TMR3_INTERRUPT_CLEAR_FLAG();
    if(TMR3_InterruptHandler)
    {
        TMR3_InterruptHandler();
    }
}

void EUSART_TX_ISR(void){
    EUSART_TX_INTERRUPT_CLEAR_FLAG();
    if(EUSART_TX_InterruptHandler)
    {
        EUSART_TX_InterruptHandler();
    }
}

void EUSART_RX_ISR(void){
    EUSART_RX_INTERRUPT_CLEAR_FLAG();
    if(EUSART_RX_InterruptHandler)
    {
        EUSART_RX_InterruptHandler();
    }
}

void I2C_ISR(void)
{
    I2C_INTERRUPT_CLEAR_FLAG();
    I2C_BUS_COL_CLEAR_FLAG();
    if(I2C_InterruptHandler)
    {
        I2C_InterruptHandler();
    }
}
void I2C_BC_ISR(void){
    I2C_INTERRUPT_CLEAR_FLAG();
    I2C_BUS_COL_CLEAR_FLAG();
    if(I2C_BC_InterruptHandler)
    {
        I2C_BC_InterruptHandler();
    }   
}

void SPI_ISR(void)
{
    SPI_INTERRUPT_CLEAR_FLAG();
    if(SPI_InterruptHandler)
    {
        SPI_InterruptHandler();
    }
}

void CCP1_ISR(void){
    CCP1_INTERRUPT_CLEAR_FLAG();
    if(CCP1_InterruptHandler)
    {
        CCP1_InterruptHandler();
    }
}

void CCP2_ISR(void)
{
    CCP2_INTERRUPT_CLEAR_FLAG();
    if(CCP2_InterruptHandler)
    {
        CCP2_InterruptHandler();
    }
}