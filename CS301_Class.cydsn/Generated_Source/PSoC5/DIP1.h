/*******************************************************************************
* File Name: DIP1.h  
* Version 2.20
*
* Description:
*  This file contains Pin function prototypes and register defines
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_DIP1_H) /* Pins DIP1_H */
#define CY_PINS_DIP1_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "DIP1_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 DIP1__PORT == 15 && ((DIP1__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    DIP1_Write(uint8 value);
void    DIP1_SetDriveMode(uint8 mode);
uint8   DIP1_ReadDataReg(void);
uint8   DIP1_Read(void);
void    DIP1_SetInterruptMode(uint16 position, uint16 mode);
uint8   DIP1_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the DIP1_SetDriveMode() function.
     *  @{
     */
        #define DIP1_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define DIP1_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define DIP1_DM_RES_UP          PIN_DM_RES_UP
        #define DIP1_DM_RES_DWN         PIN_DM_RES_DWN
        #define DIP1_DM_OD_LO           PIN_DM_OD_LO
        #define DIP1_DM_OD_HI           PIN_DM_OD_HI
        #define DIP1_DM_STRONG          PIN_DM_STRONG
        #define DIP1_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define DIP1_MASK               DIP1__MASK
#define DIP1_SHIFT              DIP1__SHIFT
#define DIP1_WIDTH              1u

/* Interrupt constants */
#if defined(DIP1__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in DIP1_SetInterruptMode() function.
     *  @{
     */
        #define DIP1_INTR_NONE      (uint16)(0x0000u)
        #define DIP1_INTR_RISING    (uint16)(0x0001u)
        #define DIP1_INTR_FALLING   (uint16)(0x0002u)
        #define DIP1_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define DIP1_INTR_MASK      (0x01u) 
#endif /* (DIP1__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define DIP1_PS                     (* (reg8 *) DIP1__PS)
/* Data Register */
#define DIP1_DR                     (* (reg8 *) DIP1__DR)
/* Port Number */
#define DIP1_PRT_NUM                (* (reg8 *) DIP1__PRT) 
/* Connect to Analog Globals */                                                  
#define DIP1_AG                     (* (reg8 *) DIP1__AG)                       
/* Analog MUX bux enable */
#define DIP1_AMUX                   (* (reg8 *) DIP1__AMUX) 
/* Bidirectional Enable */                                                        
#define DIP1_BIE                    (* (reg8 *) DIP1__BIE)
/* Bit-mask for Aliased Register Access */
#define DIP1_BIT_MASK               (* (reg8 *) DIP1__BIT_MASK)
/* Bypass Enable */
#define DIP1_BYP                    (* (reg8 *) DIP1__BYP)
/* Port wide control signals */                                                   
#define DIP1_CTL                    (* (reg8 *) DIP1__CTL)
/* Drive Modes */
#define DIP1_DM0                    (* (reg8 *) DIP1__DM0) 
#define DIP1_DM1                    (* (reg8 *) DIP1__DM1)
#define DIP1_DM2                    (* (reg8 *) DIP1__DM2) 
/* Input Buffer Disable Override */
#define DIP1_INP_DIS                (* (reg8 *) DIP1__INP_DIS)
/* LCD Common or Segment Drive */
#define DIP1_LCD_COM_SEG            (* (reg8 *) DIP1__LCD_COM_SEG)
/* Enable Segment LCD */
#define DIP1_LCD_EN                 (* (reg8 *) DIP1__LCD_EN)
/* Slew Rate Control */
#define DIP1_SLW                    (* (reg8 *) DIP1__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define DIP1_PRTDSI__CAPS_SEL       (* (reg8 *) DIP1__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define DIP1_PRTDSI__DBL_SYNC_IN    (* (reg8 *) DIP1__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define DIP1_PRTDSI__OE_SEL0        (* (reg8 *) DIP1__PRTDSI__OE_SEL0) 
#define DIP1_PRTDSI__OE_SEL1        (* (reg8 *) DIP1__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define DIP1_PRTDSI__OUT_SEL0       (* (reg8 *) DIP1__PRTDSI__OUT_SEL0) 
#define DIP1_PRTDSI__OUT_SEL1       (* (reg8 *) DIP1__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define DIP1_PRTDSI__SYNC_OUT       (* (reg8 *) DIP1__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(DIP1__SIO_CFG)
    #define DIP1_SIO_HYST_EN        (* (reg8 *) DIP1__SIO_HYST_EN)
    #define DIP1_SIO_REG_HIFREQ     (* (reg8 *) DIP1__SIO_REG_HIFREQ)
    #define DIP1_SIO_CFG            (* (reg8 *) DIP1__SIO_CFG)
    #define DIP1_SIO_DIFF           (* (reg8 *) DIP1__SIO_DIFF)
#endif /* (DIP1__SIO_CFG) */

/* Interrupt Registers */
#if defined(DIP1__INTSTAT)
    #define DIP1_INTSTAT            (* (reg8 *) DIP1__INTSTAT)
    #define DIP1_SNAP               (* (reg8 *) DIP1__SNAP)
    
	#define DIP1_0_INTTYPE_REG 		(* (reg8 *) DIP1__0__INTTYPE)
#endif /* (DIP1__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_DIP1_H */


/* [] END OF FILE */
