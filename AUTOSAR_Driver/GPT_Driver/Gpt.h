 /******************************************************************************
 *
 * Module: Gpt
 *
 * File Name: Gpt.h
 *
 * Description: Header file for TM4C123GH6PM Microcontroller - GPT Timer Driver.
 *
 * Author: Adham Muhammed
 ******************************************************************************/
#ifndef GPT_H_
#define GPT_H_

/* Id for the company in the AUTOSAR
 * for example EDGES = 1000 */
#define GPT_VENDOR_ID    (1000U)

/* Gpt Module Id */
#define GPT_MODULE_ID    (100U)

/* Gpt Instance Id */
#define GPT_INSTANCE_ID  (0U)

/*
 * Module Version 1.0.0
 */
#define GPT_SW_MAJOR_VERSION           (1U)
#define GPT_SW_MINOR_VERSION           (0U)
#define GPT_SW_PATCH_VERSION           (0U)

/*
 * AUTOSAR Version 4.0.3
 */
#define GPT_AR_RELEASE_MAJOR_VERSION   (4U)
#define GPT_AR_RELEASE_MINOR_VERSION   (0U)
#define GPT_AR_RELEASE_PATCH_VERSION   (3U)

/* Standard AUTOSAR types */
#include "Std_Types.h"

/* AUTOSAR checking between Std Types and Gpt Modules */
#if ((STD_TYPES_AR_RELEASE_MAJOR_VERSION != GPT_AR_RELEASE_MAJOR_VERSION)\
 ||  (STD_TYPES_AR_RELEASE_MINOR_VERSION != GPT_AR_RELEASE_MINOR_VERSION)\
 ||  (STD_TYPES_AR_RELEASE_PATCH_VERSION != GPT_AR_RELEASE_PATCH_VERSION))
  #error "The AR version of Std_Types.h does not match the expected version"
#endif

/* Gpt Pre-Compile Configuration Header file */
#include "Gpt_Cfg.h"

/* AUTOSAR Version checking between Gpt_Cfg.h and Gpt.h files */
#if ((GPT_CFG_AR_RELEASE_MAJOR_VERSION != GPT_AR_RELEASE_MAJOR_VERSION)\
 ||  (GPT_CFG_AR_RELEASE_MINOR_VERSION != GPT_AR_RELEASE_MINOR_VERSION)\
 ||  (GPT_CFG_AR_RELEASE_PATCH_VERSION != GPT_AR_RELEASE_PATCH_VERSION))
  #error "The AR version of Gpt_Cfg.h does not match the expected version"
#endif

/* Software Version checking between Gpt_Cfg.h and Gpt.h files */
#if ((GPT_CFG_SW_MAJOR_VERSION != GPT_SW_MAJOR_VERSION)\
 ||  (GPT_CFG_SW_MINOR_VERSION != GPT_SW_MINOR_VERSION)\
 ||  (GPT_CFG_SW_PATCH_VERSION != GPT_SW_PATCH_VERSION))
  #error "The SW version of Gpt_Cfg.h does not match the expected version"
#endif

#include "Gpt_PBcfg.h"
/* AUTOSAR Version checking between Gpt_PBcfg.h and Gpt.h files */
#if ((GPT_PBCFG_AR_RELEASE_MAJOR_VERSION != GPT_AR_RELEASE_MAJOR_VERSION)\
 ||  (GPT_PBCFG_AR_RELEASE_MINOR_VERSION != GPT_AR_RELEASE_MINOR_VERSION)\
 ||  (GPT_PBCFG_AR_RELEASE_PATCH_VERSION != GPT_AR_RELEASE_PATCH_VERSION))
  #error "The AR version of Gpt_PBcfg.h does not match the expected version"
#endif

/* Software Version checking between Gpt_PBcfg.h and Gpt.h files */
#if ((GPT_PBCFG_SW_MAJOR_VERSION != GPT_SW_MAJOR_VERSION)\
 ||  (GPT_PBCFG_SW_MINOR_VERSION != GPT_SW_MINOR_VERSION)\
 ||  (GPT_PBCFG_SW_PATCH_VERSION != GPT_SW_PATCH_VERSION))
  #error "The SW version of Gpt_PBcfg.h does not match the expected version"
#endif

/******************************************************************************
 *                      API Service Id Macros                                 *
******************************************************************************/
/* Service ID for return version of the GPT Driver. */
#define GPT_GET_VERSION_INFO_SID          (uint8)0x00

/* Service ID for Initializes the hardware timer module (GPT Driver) . */
#define GPT_INIT_SID                    (uint8)0x01

/* Service ID for Deinitializes all hardware timer channels. */
#define GPT_DEINIT_SID                  (uint8)0x02

/* Service ID for Returns the time already elapsed.  */
#define GPT_GET_TIME_ELAPSED_SID          (uint8)0x03

/* Service ID for Returns the time remaining until the target time is reached.  */
#define GPT_GET_TIME_REMAINING_SID        (uint8)0x04

/* Service ID for starting the timer channel. */
#define GPT_START_TIMER_SID              (uint8)0x05

/* Service ID for stopping the timer channel. */
#define GPT_STOP_TIMER_SID               (uint8)0x06

/* Service ID for Enables the interrupt notification for a channel (relevant in normal mode). */
#define GPT_ENABLE_NOTIFICATION_SID      (uint8)0x07

/* Service ID for Disables the interrupt notification for a channel (relevant in normal mode). */
#define GPT_DISABLE_NOTIFICATION_SID     (uint8)0x08

/* Service ID for Sets the operation mode of the GPT. */
#define GPT_SET_MODE_SID                 (uint8)0x09

/* Service ID for Disables the wakeup interrupt of a channel (relevant in sleep mode). */
#define GPT_DISABLE_WAKEUP_SID           (uint8)0x0A

/* Service ID for Enables the wakeup interrupt of a channel (relevant in sleep mode).  */
#define GPT_ENABLE_WAKEUP_SID            (uint8)0x0B

/* Service ID for checking wakeup of channel. */
#define GPT_CHECK_WAKEUP_SID            (uint8)0x0C


/*******************************************************************************
 *                      DET Error Codes                                        *
 *******************************************************************************/
/* Det code used to report that An API service called without module initialization.*/
#define GPT_E_UNINIT                  (uint8)0x0A

/* Det code used to report that An API called when timer channel is still busy (running). */
#define GPT_E_BUSY                    (uint8)0x0B

/* Det code used to report that API for initialization called when already initialized. */
#define GPT_E_ALREADY_INITIALIZED     (uint8)0x0D

/* Det code used to report that API parameter checking: invalid channel */
#define GPT_E_PARAM_CHANNEL           (uint8)0x14

/* Det code used to report that API parameter checking: invalid value */
#define GPT_E_PARAM_VALUE             (uint8)0x15

/* Det code used to report that API parameter checking: invalid pointer */
#define GPT_E_PARAM_POINTER           (uint8)0x16

/* Det code used to report that API parameter checking: invalid mode */
#define GPT_E_PARAM_MODE              (uint8)0x1F


/*******************************************************************************
 *                      Function Prototypes                                    *
 *******************************************************************************/

/* Function to Initializes the hardware timer module. */
void Gpt_Init (
        const Gpt_ConfigType* ConfigPtr
);

#if (GPT_DEINIT_API==STD_ON)
/* Function Deinitializes all hardware timer channels.*/
void Gpt_DeInit(void);
#endif

/* Function to Starts a timer channel. */
void Gpt_StartTimer(
    Gpt_ChannelType Channel,
    Gpt_ValueType Value
);

/* Function to Stops a timer channel. */
void Gpt_StopTimer(
    Gpt_ChannelType Channel
);

#if(GPT_VERSION_INFO_API==STD_ON)
/* Function to Returns the version information of GPT module*/
void Gpt_GetVersionInfo(
        Std_VersionInfoType* VersionInfoPtr
);
#endif

#if(GPT_TIME_ELAPSED_API==STD_ON)
/* Function to Returns the time already elapsed.*/
Gpt_ValueType Gpt_GetTimeElapsed(
        Gpt_ChannelType Channel
);
#endif

#if(GPT_TIME_REMAINING_API==STD_ON)
/* Function to Returns the time remaining until the target time is reached. */
Gpt_ValueType Gpt_GetTimeRemaining(
    Gpt_ChannelType Channel
);
#endif


#if(GPT_ENABLE_DISABLE_NOTIFICATION_API==STD_ON)

/* Function to Enables the interrupt notification for a channel (relevant in normal mode). */
void Gpt_EnableNotification(
    Gpt_ChannelType Channel
);

/*Disables the interrupt notification for a channel (relevant in normal mode). */
void Gpt_DisableNotification(
    Gpt_ChannelType Channel
);

#endif

#if(GPT_WAKEUP_FUNCTIONALITY_API==STD_ON)

/* Function to Sets the operation mode of the GPT (GPT_MODE_NORMAL /GPT_MODE_SLEEP).*/
void Gpt_SetMode(
    Gpt_ModeType Mode
);

/* Disables the wakeup interrupt of a channel (relevant in sleep mode) */
void Gpt_DisableWakeup(
    Gpt_ChannelType Channel
);

/* Function to Enables the wakeup interrupt of a channel (relevant in sleep mode) */
void Gpt_EnableWakeup(
    Gpt_ChannelType Channel
);

#endif


/*******************************************************************************
 *                       Timers IDs                                           *
*******************************************************************************/

/* SysTick Timer */
#define SYSTICK_TIMER       (uint8)0

/* In the next enhancement, we may integration of tiva-c timers.*/

#endif /* GPT_H_ */
