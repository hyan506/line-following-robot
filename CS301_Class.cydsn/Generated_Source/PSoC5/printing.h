/*******************************************************************************
* File Name: printing.h
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
#if !defined(CY_ISR_printing_H)
#define CY_ISR_printing_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void printing_Start(void);
void printing_StartEx(cyisraddress address);
void printing_Stop(void);

CY_ISR_PROTO(printing_Interrupt);

void printing_SetVector(cyisraddress address);
cyisraddress printing_GetVector(void);

void printing_SetPriority(uint8 priority);
uint8 printing_GetPriority(void);

void printing_Enable(void);
uint8 printing_GetState(void);
void printing_Disable(void);

void printing_SetPending(void);
void printing_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the printing ISR. */
#define printing_INTC_VECTOR            ((reg32 *) printing__INTC_VECT)

/* Address of the printing ISR priority. */
#define printing_INTC_PRIOR             ((reg8 *) printing__INTC_PRIOR_REG)

/* Priority of the printing interrupt. */
#define printing_INTC_PRIOR_NUMBER      printing__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable printing interrupt. */
#define printing_INTC_SET_EN            ((reg32 *) printing__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the printing interrupt. */
#define printing_INTC_CLR_EN            ((reg32 *) printing__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the printing interrupt state to pending. */
#define printing_INTC_SET_PD            ((reg32 *) printing__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the printing interrupt. */
#define printing_INTC_CLR_PD            ((reg32 *) printing__INTC_CLR_PD_REG)


#endif /* CY_ISR_printing_H */


/* [] END OF FILE */
