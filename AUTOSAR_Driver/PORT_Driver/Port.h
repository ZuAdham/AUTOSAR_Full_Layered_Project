/******************************************************************************
 *
 * Module: Port
 *
 * File Name: Port.h
 *
 * Description: Header file for TM4C123GH6PM Microcontroller - Port Driver.
 *
 * Author: Adham Muhammed
 ******************************************************************************/

#ifndef PORT_H
#define PORT_H

/* Id for the company in the AUTOSAR
 * for example EDGES = 1000 */
#define PORT_VENDOR_ID    (1000U)

/* Port Module Id */
#define PORT_MODULE_ID    (124U)

/* Port Instance Id */
#define PORT_INSTANCE_ID  (0U)

/*
 * Module Version 1.0.0
 */
#define PORT_SW_MAJOR_VERSION           (1U)
#define PORT_SW_MINOR_VERSION           (0U)
#define PORT_SW_PATCH_VERSION           (0U)

/*
 * AUTOSAR Version 4.0.3
 */
#define PORT_AR_RELEASE_MAJOR_VERSION   (4U)
#define PORT_AR_RELEASE_MINOR_VERSION   (0U)
#define PORT_AR_RELEASE_PATCH_VERSION   (3U)

/* Standard AUTOSAR types */
#include "Std_Types.h"

/* AUTOSAR checking between Std Types and Port Module */
#if ((STD_TYPES_AR_RELEASE_MAJOR_VERSION != PORT_AR_RELEASE_MAJOR_VERSION)\
        ||  (STD_TYPES_AR_RELEASE_MINOR_VERSION != PORT_AR_RELEASE_MINOR_VERSION)\
        ||  (STD_TYPES_AR_RELEASE_PATCH_VERSION != PORT_AR_RELEASE_PATCH_VERSION))
#error "The AR version of Std_Types.h does not match the expected version"
#endif

/* Port Pre-Compile Configuration Header file */
#include "Port_Cfg.h"

/* AUTOSAR Version checking between Port_Cfg.h and Port.h files */
#if ((PORT_CFG_AR_RELEASE_MAJOR_VERSION != PORT_AR_RELEASE_MAJOR_VERSION)\
        ||  (PORT_CFG_AR_RELEASE_MINOR_VERSION != PORT_AR_RELEASE_MINOR_VERSION)\
        ||  (PORT_CFG_AR_RELEASE_PATCH_VERSION != PORT_AR_RELEASE_PATCH_VERSION))
#error "The AR version of Port_Cfg.h does not match the expected version"
#endif

/* Software Version checking between Port_Cfg.h and Port.h files */
#if ((PORT_CFG_SW_MAJOR_VERSION != PORT_SW_MAJOR_VERSION)\
        ||  (PORT_CFG_SW_MINOR_VERSION != PORT_SW_MINOR_VERSION)\
        ||  (PORT_CFG_SW_PATCH_VERSION != PORT_SW_PATCH_VERSION))
#error "The SW version of Port_Cfg.h does not match the expected version"
#endif

#include "port_PBcfg.h"

/* AUTOSAR Version checking between Port_PBcfg.h and Port.h files */
#if ((PORT_PBCFG_AR_RELEASE_MAJOR_VERSION != PORT_AR_RELEASE_MAJOR_VERSION)\
        ||  (PORT_PBCFG_AR_RELEASE_MINOR_VERSION != PORT_AR_RELEASE_MINOR_VERSION)\
        ||  (PORT_PBCFG_AR_RELEASE_PATCH_VERSION != PORT_AR_RELEASE_PATCH_VERSION))
#error "The AR version of Port_PBcfg.h does not match the expected version"
#endif

/* Software Version checking between Port_PBcfg.h and Port.h files */
#if ((PORT_PBCFG_SW_MAJOR_VERSION != PORT_SW_MAJOR_VERSION)\
        ||  (PORT_PBCFG_SW_MINOR_VERSION != PORT_SW_MINOR_VERSION)\
        ||  (PORT_PBCFG_SW_PATCH_VERSION != PORT_SW_PATCH_VERSION))
#error "The SW version of Port_PBcfg.h does not match the expected version"
#endif

/******************************************************************************
 *                      API Service Id Macros                                 *
 ******************************************************************************/
/* Service ID for Port Init */
#define PORT_INIT_SID                           (uint8)0x00

/* Service ID for Port Set Channel direction */
#define PORT_SET_PIN_DIRECTION_SID              (uint8)0x01

/* Service ID for Port Refresh Port Direction */
#define PORT_REFRESH_Port_DIRECTION_SID         (uint8)0x02

/* Service ID for Port Get Version Info  */
#define PORT_GET_VERSION_INFO_SID               (uint8)0x03

/* Service ID for Port Set Pin Mode */
#define PORT_SET_PIN_MODE_SID                   (uint8)0x04

/*******************************************************************************
 *                      DET Error Codes                                        *
 *******************************************************************************/
/* Det code used to report Invalid Port Pin ID requested */
#define PORT_E_PARAM_PIN                        (uint8)0x0A

/* Det code used to report Port Pin not configured as changeable */
#define PORT_E_DIRECTION_UNCHANGEABLE           (uint8)0x0B

/* Det code used to report API Port_Init service called with wrong parameter. */
#define PORT_E_PARAM_CONFIG                     (uint8)0x0C

/* Det code used to report API Port_SetPinMode service called when mode is unchangeable. */
#define PORT_E_PARAM_INVALID_MODE               (uint8)0x0D

/* Det code used to report API Port_SetPinMode service called when mode is unchangeable. */
#define PORT_E_MODE_UNCHANGEABLE                (uint8)0x0E

/*  Det code used to report that API service called without module initialization.  */
#define PORT_E_UNINIT                           (uint8)0x0F

/*  Det code used to report that API called with a Null Pointer */
#define PORT_E_PARAM_POINTER                    (uint8)0x10


/*******************************************************************************
 *                      Function Prototypes                                    *
 *******************************************************************************/

/* Function for PORT Initialization API */
void Port_Init(
        const Port_ConfigType* ConfigPtr
);

/* Function for PORT Set Channel Direction API */
#if (PORT_SET_PIN_DIRECTION_API == STD_ON)
void Port_SetPinDirection(
        Port_PinType Pin,
        Port_PinDirectionType Direction
);
#endif

/* Function to Refreshes port direction.*/
void Port_RefreshPortDirection(void);

/* Function for PORT Get Version Info API */
#if (PORT_VERSION_INFO_API == STD_ON)
void Port_GetVersionInfo(
        Std_VersionInfoType* versioninfo
);
#endif

#if(PORT_SET_PIN_MODE_API==STD_ON)
void Port_SetPinMode(
        Port_PinType Pin,
        Port_PinModeType Mode
);
#endif

/*******************************************************************************
 *                              Module Definitions                             *
 *******************************************************************************/
/*Port ID for TM4C123GH6PM */
#define PORTA_ID                (Port_Type)0
#define PORTB_ID                (Port_Type)1
#define PORTC_ID                (Port_Type)2
#define PORTD_ID                (Port_Type)3
#define PORTE_ID                (Port_Type)4
#define PORTF_ID                (Port_Type)5

/*Pin ID for TM4C123GH6PM */
#define PORT_PIN_0_ID           (Port_PinType)0
#define PORT_PIN_1_ID           (Port_PinType)1
#define PORT_PIN_2_ID           (Port_PinType)2
#define PORT_PIN_3_ID           (Port_PinType)3
#define PORT_PIN_4_ID           (Port_PinType)4
#define PORT_PIN_5_ID           (Port_PinType)5
#define PORT_PIN_6_ID           (Port_PinType)6
#define PORT_PIN_7_ID           (Port_PinType)7


#endif /* PORT_H */
