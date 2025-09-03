 /******************************************************************************
 *
 * Module: Gpt
 *
 * File Name: Gpt_Cfg.h
 *
 * Description: Pre-Compile Configuration Header file for TM4C123GH6PM Microcontroller - Gpt Driver
 *
 * Author: Adham Muhammed
 ******************************************************************************/

#ifndef GPT_CFG_H_
#define GPT_CFG_H_

/*
 * Module Version 1.0.0
 */
#define GPT_CFG_SW_MAJOR_VERSION              (1U)
#define GPT_CFG_SW_MINOR_VERSION              (0U)
#define GPT_CFG_SW_PATCH_VERSION              (0U)

/*
 * AUTOSAR Version 4.0.3
 */
#define GPT_CFG_AR_RELEASE_MAJOR_VERSION     (4U)
#define GPT_CFG_AR_RELEASE_MINOR_VERSION     (0U)
#define GPT_CFG_AR_RELEASE_PATCH_VERSION     (3U)

/*Open chapter Configuration specification in sws and search for all pre-compile config */

/*******************************************************************************
*                              Pre-Compile configurations                      *
*******************************************************************************/

/* Pre-compile option for Development Error Detect */
#define GPT_DEV_ERROR_DETECT                    (STD_ON)

/* Pre-compile option for report wakeup source */
#define GPT_REPORT_WAKEUP_SOURCE                (STD_OFF)

/* Pre-compile option for Adds / removes the service Gpt_DeInit() from the code */
#define GPT_DEINIT_API                          (STD_ON)

/* Pre-compile option for Adds / removes the services Gpt_EnableNotification() and Gpt_DisableNotification from the code.  */
#define GPT_ENABLE_DISABLE_NOTIFICATION_API     (STD_ON)

/* Pre-compile option for Adds / removes the service Gpt_GetTimeElapsed() from the code */
#define GPT_TIME_ELAPSED_API                    (STD_ON)

/* Pre-compile option for Adds / removes the service Gpt_GetTimeRemaining() from the code */
#define GPT_TIME_REMAINING_API                  (STD_ON)

/* Pre-compile option for Adds / removes the service Gpt_GetVersionInfo() from the code */
#define GPT_VERSION_INFO_API                    (STD_OFF)

/* Pre-compile option for Adds / removes the services Gpt_SetMode(), Gpt_EnableWakeup() Gpt_DisableWakeup() and Gpt_CheckWakeup() from the code.  */
#define GPT_WAKEUP_FUNCTIONALITY_API            (STD_OFF)

/* Number of the configured GPT TIMERS */
#define GPT_CONFIGURED_CHANNLES                    (1U)

/* Channel Index in the array of structures in Gpt_PBcfg.c */
#define SYSTICK_CHANNEL_ID_INDEX                (uint8)0x00

/*Systick Priority*/
#define SYSTICK_INTERRUPT_PRIORITY              1

#endif /* GPT_CFG_H_ */
