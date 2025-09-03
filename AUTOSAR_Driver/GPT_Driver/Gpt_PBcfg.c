 /******************************************************************************
 *
 * Module: GPT
 *
 * File Name: Gpt_PBcfg.c
 *
 * Description: Post Build Configuration Source file for TM4C123GH6PM Microcontroller - GPT Driver
 *
 * Author: Adham Muhammed
 ******************************************************************************/
#include "Gpt.h"

extern void Os_NewTimerTick(void);
/*
 * Module Version 1.0.0
 */
#define GPT_PBCFG_SW_MAJOR_VERSION              (1U)
#define GPT_PBCFG_SW_MINOR_VERSION              (0U)
#define GPT_PBCFG_SW_PATCH_VERSION              (0U)

/*
 * AUTOSAR Version 4.0.3
 */
#define GPT_PBCFG_AR_RELEASE_MAJOR_VERSION     (4U)
#define GPT_PBCFG_AR_RELEASE_MINOR_VERSION     (0U)
#define GPT_PBCFG_AR_RELEASE_PATCH_VERSION     (3U)

/* AUTOSAR Version checking between Gpt_PBcfg and Gpt.h files */
#if ((GPT_PBCFG_AR_RELEASE_MAJOR_VERSION != GPT_AR_RELEASE_MAJOR_VERSION)\
 ||  (GPT_PBCFG_AR_RELEASE_MINOR_VERSION != GPT_AR_RELEASE_MINOR_VERSION)\
 ||  (GPT_PBCFG_AR_RELEASE_PATCH_VERSION != GPT_AR_RELEASE_PATCH_VERSION))
  #error "The AR version of Gpt_PBcfg.c does not match the expected version"
#endif

/* Software Version checking between Gpt_PBcfg.c and Gpt.h files */
#if ((GPT_PBCFG_SW_MAJOR_VERSION != GPT_SW_MAJOR_VERSION)\
 ||  (GPT_PBCFG_SW_MINOR_VERSION != GPT_SW_MINOR_VERSION)\
 ||  (GPT_PBCFG_SW_PATCH_VERSION != GPT_SW_PATCH_VERSION))
  #error "The SW version of Gpt_PBcfg.c does not match the expected version"
#endif

const Gpt_ConfigType Gpt_ConfigPtr = {
                                      SYSTICK_TIMER,GPT_MODE_NORMAL,GPT_CONTINUOUS,16000,Os_NewTimerTick
};
