/* 
 * File:   mcal_internal_interrupt.h
 * Author: Walid Omar
 *
 * Created on December 31, 2022, 9:23 PM
 */

#ifndef MCAL_INTERNAL_INTERRUPT_H
#define	MCAL_INTERNAL_INTERRUPT_H

/* Includes Section */

#include "mcal_interrupt_config.h"

/* Macros Declarations  */
#define ADC_INTERRUPT_FEATURE   INTERRUPT_FEATURE_ENABLE
#define TMR0_INTERRUPT_FEATURE  INTERRUPT_FEATURE_ENABLE
#define TMR1_INTERRUPT_FEATURE  INTERRUPT_FEATURE_ENABLE
#define TMR2_INTERRUPT_FEATURE  INTERRUPT_FEATURE_ENABLE
#define TMR3_INTERRUPT_FEATURE  INTERRUPT_FEATURE_ENABLE
#define EUSART_TX_INTERRUPT_FEATURE_ENABLE  INTERRUPT_FEATURE_ENABLE
#define EUSART_RX_INTERRUPT_FEATURE_ENABLE  INTERRUPT_FEATURE_ENABLE
#define I2C_INTERRUPT_FEATURE_ENABLE    INTERRUPT_FEATURE_ENABLE
#define SPI_INTERRUPT_FEATURE_ENABLE    INTERRUPT_FEATURE_ENABLE
#define CCP1_INTERRUPT_FEATURE_ENABLE   INTERRUPT_FEATURE_ENABLE
#define CCP2_INTERRUPT_FEATURE_ENABLE   INTERRUPT_FEATURE_ENABLE

/* Macro Functions Declarations */

// ADC MACRO FUNCTIONS 
#if ADC_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
#define ADC_INTERRUPT_ENABLE()          (PIE1bits.ADIE = 1)
#define ADC_INTERRUPT_DISABLE()         (PIE1bits.ADIE = 0)
#define ADC_INTERRUPT_CLEAR_FLAG()      (PIR1bits.ADIF = 0)
#if INTERRUPT_FEATURE == INTERRUPT_PRIORITY_ENABLE
#define ADC_INTERRUPT_HIGH_PRIORITY()   (IPR1bits.ADIP = 1)
#define ADC_INTERRUPT_LOW_PRIORITY()    (IPR1bits.ADIP = 0)
#endif
#endif

// TIMER0 MACRO FUNCTIONS
#if TMR0_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
#define TMR0_INTERRUPT_ENABLE()          (INTCONbits.TMR0IE = 1)
#define TMR0_INTERRUPT_DISABLE()         (INTCONbits.TMR0IE = 0)
#define TMR0_INTERRUPT_CLEAR_FLAG()      (INTCONbits.TMR0IF = 0)
#if INTERRUPT_FEATURE == INTERRUPT_PRIORITY_ENABLE
#define TMR0_INTERRUPT_HIGH_PRIORITY()   (INTCON2bits.TMR0IP = 1)
#define TMR0_INTERRUPT_LOW_PRIORITY()    (INTCON2bits.TMR0IP  = 0)
#endif
#endif

// TIMER1 MACRO FUNCTIONS
#if TMR1_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
#define TMR1_INTERRUPT_ENABLE()          (PIE1bits.TMR1IE = 1)
#define TMR1_INTERRUPT_DISABLE()         (PIE1bits.TMR1IE = 0)
#define TMR1_INTERRUPT_CLEAR_FLAG()      (PIR1bits.TMR1IF = 0)
#if INTERRUPT_FEATURE == INTERRUPT_PRIORITY_ENABLE
#define TMR1_INTERRUPT_HIGH_PRIORITY()   (IPR1bits.TMR1IP = 1)
#define TMR1_INTERRUPT_LOW_PRIORITY()    (IPR1bits.TMR1IP = 0)
#endif
#endif

// TIMER2 MACRO FUNCTIONS
#if TMR2_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
#define TMR2_INTERRUPT_ENABLE()          (PIE1bits.TMR2IE = 1)
#define TMR2_INTERRUPT_DISABLE()         (PIE1bits.TMR2IE = 0)
#define TMR2_INTERRUPT_CLEAR_FLAG()      (PIR1bits.TMR2IF = 0)
#if INTERRUPT_FEATURE == INTERRUPT_PRIORITY_ENABLE
#define TMR2_INTERRUPT_HIGH_PRIORITY()   (IPR1bits.TMR2IP = 1)
#define TMR2_INTERRUPT_LOW_PRIORITY()    (IPR1bits.TMR2IP = 0)
#endif
#endif

// TIMER3 MACRO FUNCTIONS
#if TMR3_INTERRUPT_FEATURE == INTERRUPT_FEATURE_ENABLE
#define TMR3_INTERRUPT_ENABLE()          (PIE2bits.TMR3IE = 1)
#define TMR3_INTERRUPT_DISABLE()         (PIE2bits.TMR3IE = 0)
#define TMR3_INTERRUPT_CLEAR_FLAG()      (PIR2bits.TMR3IF = 0)
#if INTERRUPT_FEATURE == INTERRUPT_PRIORITY_ENABLE
#define TMR3_INTERRUPT_HIGH_PRIORITY()   (IPR2bits.TMR3IP = 1)
#define TMR3_INTERRUPT_LOW_PRIORITY()    (IPR2bits.TMR3IP = 0)
#endif
#endif

// EUSART_TX MACRO FUNCTIONS
#if EUSART_TX_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
#define EUSART_TX_INTERRUPT_ENABLE()        (PIE1bits.TXIE == 1)
#define EUSART_TX_INTERRUPT_DISABLE()       (PIE1bits.TXIE == 0)
#define EUSART_TX_INTERRUPT_CLEAR_FLAG()    (PIR1bits.TXIF == 0)
#if INTERRUPT_FEATURE == INTERRUPT_PRIORITY_ENABLE
#define EUSART_TX_INTERRUPT_HIGH_PRIORITY() (IPR1bits.TXIP=1)
#define EUSART_TX_INTERRUPT_LOW_PRIORITY()  (IPR1bits.TXIP=0)
#endif
#endif

// EUSART_RX MACRO FUNCTIONS
#if EUSART_TX_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
#define EUSART_RX_INTERRUPT_ENABLE()        (PIE1bits.RCIE == 1)
#define EUSART_RX_INTERRUPT_DISABLE()       (PIE1bits.RCIE == 0)
#define EUSART_RX_INTERRUPT_CLEAR_FLAG()    (PIR1bits.RCIF == 0)
#if INTERRUPT_FEATURE == INTERRUPT_PRIORITY_ENABLE
#define EUSART_RX_INTERRUPT_HIGH_PRIORITY() (IPR1bits.RCIP=1)
#define EUSART_RX_INTERRUPT_LOW_PRIORITY()  (IPR1bits.RCIP=0)
#endif
#endif

// I2C MACROS FUNCTIONS 
#if I2C_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
#define I2C_INTERRUPT_ENABLE()          (PIE1bits.SSPIE = 1)
#define I2C_BUS_COL_ENABLE()            (PIE2bits.BCLIE = 1)
#define I2C_INTERRUPT_DISABLE()         (PIE1bits.SSPIE = 0)
#define I2C_BUS_COL_DISABLE()           (PIE2bits.BCLIE = 0)
#define I2C_INTERRUPT_CLEAR_FLAG()      (PIR1bits.SSPIF = 0)
#define I2C_BUS_COL_CLEAR_FLAG()        (PIR2bits.BCLIF = 0)
#if INTERRUPT_FEATURE == INTERRUPT_PRIORITY_ENABLE
#define I2C_INTERRUPT_HIGH_PRIORITY()   (IPR1bits.SSPIP = 1)
#define I2C_BUS_COL_HIGH_PRIORITY()     (IPR2bits.BCLIP = 1)
#define I2C_INTERRUPT_LOW_PRIORITY()    (IPR1bits.SSPIP = 0)
#define I2C_BUS_COL_LOW_PRIORITY()      (IPR2bits.BCLIP = 0)
#endif
#endif

// SPI MACROS FUNCTIONS
#if SPI_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
#define SPI_INTERRUPT_ENABLE()          (PIE1bits.SSPIE = 1)
#define SPI_INTERRUPT_DISABLE()         (PIE1bits.SSPIE = 0)
#define SPI_INTERRUPT_CLEAR_FLAG()      (PIR1bits.SSPIF = 0)
#if INTERRUPT_FEATURE == INTERRUPT_PRIORITY_ENABLE
#define SPI_INTERRUPT_HIGH_PRIORITY()   (IPR1bits.SSPIP = 1)
#define SPI_INTERRUPT_LOW_PRIORITY()   (IPR1bits.SSPIP = 0)
#endif
#endif

// CCP1 MACROS FUNCTIONS
#if CCP1_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
#define CCP1_INTERRUPT_ENABLE()         (PIE1bits.CCP1IE = 1)
#define CCP1_INTERRUPT_DISABLE()        (PIE1bits.CCP1IE = 0)
#define CCP1_INTERRUPT_CLEAR_FLAG()     (PIR1bits.CCP1IF = 0)
#if INTERRUPT_FEATURE == INTERRUPT_PRIORITY_ENABLE
#define CCP1_INTERRUPT_HIGH_PRIORITY()  (IPR1bits.CCP1IP = 1)
#define CCP1_INTERRUPT_LOW_PRIORITY()   (IPR1bits.CCP1IP = 0)
#endif
#endif

// CCP2 MACROS FUNCTIONS
#if CCP2_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
#define CCP2_INTERRUPT_ENABLE()         (PIE2bits.CCP2IE = 1)
#define CCP2_INTERRUPT_DISABLE()        (PIE2bits.CCP2IE = 0)
#define CCP2_INTERRUPT_CLEAR_FLAG()     (PIR2bits.CCP2IF = 0)
#if INTERRUPT_FEATURE == INTERRUPT_PRIORITY_ENABLE
#define CCP2_INTERRUPT_HIGH_PRIORITY()  (IPR2bits.CCP2IP = 1)
#define CCP2_INTERRUPT_LOW_PRIORITY()   (IPR2bits.CCP2IP = 0)
#endif
#endif

/* Data Types Declarations */
typedef struct {
    void(*ADC_ExceptionHandler)(void);
    interrupt_priority  periority;    
}interrupt_ADC_t;

typedef struct {
    void(*TMR0_ExceptionHandler)(void);
    interrupt_priority  periority;  
    uint16 preload_value;
}interrupt_TMR0_t;

typedef struct {
    void(*TMR1_ExceptionHandler)(void);
    interrupt_priority  periority;  
}interrupt_TMR1_t;

typedef struct {
    void(*TMR2_ExceptionHandler)(void);
    interrupt_priority  periority;  
}interrupt_TMR2_t;

typedef struct {
    void(*TMR3_ExceptionHandler)(void);
    interrupt_priority  periority;  
}interrupt_TMR3_t;

typedef struct {
    void(*EUSART_TX_ExceptionHandler)(void);
    interrupt_priority  periority;  
}interrupt_EUSART_TX_t;

typedef struct {
    void(*EUSART_RX_ExceptionHandler)(void);
    interrupt_priority  periority;  
}interrupt_EUSART_RX_t;

typedef struct {
    void(*I2C_ExceptionHandler)(void);
    void(*BC_ExceptionHandler)(void);
    interrupt_priority  periority;  
}interrupt_I2C_t;

typedef struct {
    void(*SPI_ExceptionHandler)(void);
    interrupt_priority  periority;  
}interrupt_SPI_t;

typedef struct {
    void(*CCP1_ExceptionHandler)(void);
    interrupt_priority  periority;  
}interrupt_CCP1_t;

typedef struct {
    void(*CCP2_ExceptionHandler)(void);
    interrupt_priority  periority;  
}interrupt_CCP2_t;

/* Functions Declarations */
Std_ReturnType Interrupt_ADC_Enable(const interrupt_ADC_t *object);
Std_ReturnType Interrupt_ADC_Disable(const interrupt_ADC_t *object);

Std_ReturnType Interrupt_TMR0_Enable(const interrupt_TMR0_t *object);
Std_ReturnType Interrupt_TMR0_Disable(const interrupt_TMR0_t *object);

Std_ReturnType Interrupt_TMR1_Enable(const interrupt_TMR1_t *object);
Std_ReturnType Interrupt_TMR1_Disable(const interrupt_TMR1_t *object);

Std_ReturnType Interrupt_TMR2_Enable(const interrupt_TMR2_t *object);
Std_ReturnType Interrupt_TMR2_Disable(const interrupt_TMR2_t *object);

Std_ReturnType Interrupt_TMR3_Enable(const interrupt_TMR3_t *object);
Std_ReturnType Interrupt_TMR3_Disable(const interrupt_TMR3_t *object);

Std_ReturnType Interrupt_EUSART_TX_Enable(const interrupt_EUSART_TX_t *object);
Std_ReturnType Interrupt_EUSART_TX_Disable(const interrupt_EUSART_TX_t *object);

Std_ReturnType Interrupt_EUSART_RX_Enable(const interrupt_EUSART_RX_t *object);
Std_ReturnType Interrupt_EUSART_RX_Disable(const interrupt_EUSART_RX_t *object);

Std_ReturnType Interrupt_I2C_Enable(const interrupt_I2C_t *object);
Std_ReturnType Interrupt_I2C_Disable(const interrupt_I2C_t *object);

Std_ReturnType Interrupt_SPI_Enable(const interrupt_SPI_t *object);
Std_ReturnType Interrupt_SPI_Disable(const interrupt_SPI_t *object);

Std_ReturnType Interrupt_CCP1_Enable(const interrupt_CCP1_t *object);
Std_ReturnType Interrupt_CCP1_Disable(const interrupt_CCP1_t *object);

Std_ReturnType Interrupt_CCP2_Enable(const interrupt_CCP2_t *object);
Std_ReturnType Interrupt_CCP2_Disable(const interrupt_CCP2_t *object);

#endif	/* MCAL_INTERNAL_INTERRUPT_H */

