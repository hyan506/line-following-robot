/*******************************************************************************
* File Name: check.h
* Version 1.70
*
*  Description:
*   Provides the function definitions for the Interrupt Controller.
*
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/
#if !defined(CY_ISR_check_H)
#define CY_ISR_check_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void check_Start(void);
void check_StartEx(cyisraddress address);
void check_Stop(void);

CY_ISR_PROTO(check_Interrupt);

void check_SetVector(cyisraddress address);
cyisraddress check_GetVector(void);

void check_SetPriority(uint8 priority);
uint8 check_GetPriority(void);

void check_Enable(void);
uint8 check_GetState(void);
void check_Disable(void);

void check_SetPending(void);
void check_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the check ISR. */
#define check_INTC_VECTOR            ((reg32 *) check__INTC_VECT)

/* Address of the check ISR priority. */
#define check_INTC_PRIOR             ((reg8 *) check__INTC_PRIOR_REG)

/* Priority of the check interrupt. */
#define check_INTC_PRIOR_NUMBER      check__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable check interrupt. */
#define check_INTC_SET_EN            ((reg32 *) check__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the check interrupt. */
#define check_INTC_CLR_EN            ((reg32 *) check__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the check interrupt state to pending. */
#define check_INTC_SET_PD            ((reg32 *) check__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the check interrupt. */
#define check_INTC_CLR_PD            ((reg32 *) check__INTC_CLR_PD_REG)


#endif /* CY_ISR_check_H */


/* [] END OF FILE */
