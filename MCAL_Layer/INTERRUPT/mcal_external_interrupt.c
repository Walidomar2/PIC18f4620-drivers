/* 
 * File:   mcal_external_interrupt.h
 * Author: Walid Omar
 *
 * Created on December 31, 2022, 9:23 PM
 */

#include "mcal_external_interrupt.h"

static Std_ReturnType Enable_ka(void);

Std_ReturnType Interrupt_INTx_Enable(const interrupt_INTx_t *object){
    Std_ReturnType ret_value=E_NOT_OK;
    if(NULL == object){
        ret_value=E_NOT_OK;
        }
    else
    {
        Enable_ka();
        
    }
    return ret_value;
}

Std_ReturnType Interrupt_INTx_Disable(const interrupt_INTx_t *object){
    Std_ReturnType ret_value=E_NOT_OK;
    if(NULL == object){
        ret_value=E_NOT_OK;
        }
    else
    {
        
    }
    return ret_value;
}

Std_ReturnType Interrupt_RBx_Enable(const interrupt_RBx_t *object){
    Std_ReturnType ret_value=E_NOT_OK;
    if(NULL == object){
        ret_value=E_NOT_OK;
        }
    else
    {
        
    }
    return ret_value; 
}

Std_ReturnType Interrupt_RBx_Disable(const interrupt_RBx_t *object){
    Std_ReturnType ret_value=E_NOT_OK;
    if(NULL == object){
        ret_value=E_NOT_OK;
        }
    else
    {
        
    }
    return ret_value;
}
