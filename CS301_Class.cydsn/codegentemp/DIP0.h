/*******************************************************************************
* File Name: DIP0.h  
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

#if !defined(CY_PINS_DIP0_H) /* Pins DIP0_H */
#define CY_PINS_DIP0_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "DIP0_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 DIP0__PORT == 15 && ((DIP0__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    DIP0_Write(uint8 value);
void    DIP0_SetDriveMode(uint8 mode);
uint8   DIP0_ReadDataReg(void);
uint8   DIP0_Read(void);
void    DIP0_SetInterruptMode(uint16 position, uint16 mode);
uint8   DIP0_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the DIP0_SetDriveMode() function.
     *  @{
     */
        #define DIP0_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define DIP0_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define DIP0_DM_RES_UP          PIN_DM_RES_UP
        #define DIP0_DM_RES_DWN         PIN_DM_RES_DWN
        #define DIP0_DM_OD_LO           PIN_DM_OD_LO
        #define DIP0_DM_OD_HI           PIN_DM_OD_HI
        #define DIP0_DM_STRONG          PIN_DM_STRONG
        #define DIP0_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define DIP0_MASK               DIP0__MASK
#define DIP0_SHIFT              DIP0__SHIFT
#define DIP0_WIDTH              1u

/* Interrupt constants */
#if defined(DIP0__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in DIP0_SetInterruptMode() function.
     *  @{
     */
        #define DIP0_INTR_NONE      (uint16)(0x0000u)
        #define DIP0_INTR_RISING    (uint16)(0x0001u)
        #define DIP0_INTR_FALLING   (uint16)(0x0002u)
        #define DIP0_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define DIP0_INTR_MASK      (0x01u) 
#endif /* (DIP0__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define DIP0_PS                     (* (reg8 *) DIP0__PS)
/* Data Register */
#define DIP0_DR                     (* (reg8 *) DIP0__DR)
/* Port Number */
#define DIP0_PRT_NUM                (* (reg8 *) DIP0__PRT) 
/* Connect to Analog Globals */                                                  
#define DIP0_AG                     (* (reg8 *) DIP0__AG)                       
/* Analog MUX bux enable */
#define DIP0_AMUX                   (* (reg8 *) DIP0__AMUX) 
/* Bidirectional Enable */                                                        
#define DIP0_BIE                    (* (reg8 *) DIP0__BIE)
/* Bit-mask for Aliased Register Access */
#define DIP0_BIT_MASK               (* (reg8 *) DIP0__BIT_MASK)
/* Bypass Enable */
#define DIP0_BYP                    (* (reg8 *) DIP0__BYP)
/* Port wide control signals */                                                   
#define DIP0_CTL                    (* (reg8 *) DIP0__CTL)
/* Drive Modes */
#define DIP0_DM0                    (* (reg8 *) DIP0__DM0) 
#define DIP0_DM1                    (* (reg8 *) DIP0__DM1)
#define DIP0_DM2                    (* (reg8 *) DIP0__DM2) 
/* Input Buffer Disable Override */
#define DIP0_INP_DIS                (* (reg8 *) DIP0__INP_DIS)
/* LCD Common or Segment Drive */
#define DIP0_LCD_COM_SEG            (* (reg8 *) DIP0__LCD_COM_SEG)
/* Enable Segment LCD */
#define DIP0_LCD_EN                 (* (reg8 *) DIP0__LCD_EN)
/* Slew Rate Control */
#define DIP0_SLW                    (* (reg8 *) DIP0__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define DIP0_PRTDSI__CAPS_SEL       (* (reg8 *) DIP0__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define DIP0_PRTDSI__DBL_SYNC_IN    (* (reg8 *) DIP0__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define DIP0_PRTDSI__OE_SEL0        (* (reg8 *) DIP0__PRTDSI__OE_SEL0) 
#define DIP0_PRTDSI__OE_SEL1        (* (reg8 *) DIP0__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define DIP0_PRTDSI__OUT_SEL0       (* (reg8 *) DIP0__PRTDSI__OUT_SEL0) 
#define DIP0_PRTDSI__OUT_SEL1       (* (reg8 *) DIP0__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define DIP0_PRTDSI__SYNC_OUT       (* (reg8 *) DIP0__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(DIP0__SIO_CFG)
    #define DIP0_SIO_HYST_EN        (* (reg8 *) DIP0__SIO_HYST_EN)
    #define DIP0_SIO_REG_HIFREQ     (* (reg8 *) DIP0__SIO_REG_HIFREQ)
    #define DIP0_SIO_CFG            (* (reg8 *) DIP0__SIO_CFG)
    #define DIP0_SIO_DIFF           (* (reg8 *) DIP0__SIO_DIFF)
#endif /* (DIP0__SIO_CFG) */

/* Interrupt Registers */
#if defined(DIP0__INTSTAT)
    #define DIP0_INTSTAT            (* (reg8 *) DIP0__INTSTAT)
    #define DIP0_SNAP               (* (reg8 *) DIP0__SNAP)
    
	#define DIP0_0_INTTYPE_REG 		(* (reg8 *) DIP0__0__INTTYPE)
#endif /* (DIP0__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_DIP0_H */


/* [] END OF FILE */
