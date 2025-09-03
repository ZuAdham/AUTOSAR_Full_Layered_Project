 /******************************************************************************
 *
 * Module: GPT
 *
 * File Name: Gpt_PBcfg.h
 *
 * Description: Post Build Configuration Source file for TM4C123GH6PM Microcontroller - GPT Driver
 *
 * Author: Adham Muhammed
 ******************************************************************************/
#ifndef GPT_PBCFG_H_
#define GPT_PBCFG_H_

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

/*******************************************************************************
 *                              Module Data Types                              *
*******************************************************************************/
/* Numeric ID of a GPT channel */
typedef uint8 Gpt_ChannelType;


/* Type for reading and setting the timer values (in number of ticks). choose uint64 because The timer register width in Tiva C may extend up to 64 bits. */
typedef uint64 Gpt_ValueType;

/* Enum to allow the selection of different power modes. */
/* GPT_MODE_NORMALNormal operation mode of the GPT
 * GPT_MODE_SLEEP Operation for reduced power operation mode. In sleep mode only wakeup capable channels are available.  */
typedef enum{
  GPT_MODE_NORMAL, GPT_MODE_SLEEP
}Gpt_ModeType;

/*Note Gpt_RunningMode config parameter is for tiva-c timers ,
  The SysTick timer generates periodic interrupts at a fixed interval,
  which is set by programming the reload value in the SYST_RVR (SysTick Reload Value Register). Once the SysTick timer reaches zero,
  it reloads the value from SYST_RVR and continues counting down, generating interrupts at regular intervals.
  While the SysTick timer does not directly support one-shot operation, you can simulate it by manually disabling the SysTick timer interrupt after it triggers for the first time.
  This effectively stops further interrupts from the SysTick timer, achieving a one-shot behavior. However,
  this approach requires additional software handling and may not be as efficient as using a dedicated one-shot timer.
*/
typedef enum
{
  GPT_CONTINUOUS,GPT_ONE_SHOT
} Gpt_ChannelMode;

/* Enum for Specifies the behaviour of the timer channel after the target time is reached. */
/* GPT_CH_MODE_ONESHOT  After reaching the target time, the timer stops automatically (timer expired).
 * GPT_CH_MODE_CONTINUOUS  After reaching the target time, the timer continues running with the value "zero" again.*/
/*Note Gpt_ModeType config parameter is for Tiva-c timers only is has no effect on Systick timer*/
typedef enum
{
  INITIALIZED, RUNNING, STOPPED, EXPIRED
} Gpt_StateType;

typedef enum
{
  INTERRUPT_OFF, INTERRUPT_ON
} Gpt_InterruptOption;


typedef struct{
  Gpt_ChannelType      GptChannelId;
  Gpt_ModeType         GptMode;
  Gpt_ChannelMode      GptChannelMode;
  Gpt_ValueType        GptChannelTickFrequency;
  void                 (*GptNotifcation)(void);
}Gpt_ConfigChannel;

typedef struct{
  Gpt_ConfigChannel Gpt_Channels[GPT_CONFIGURED_CHANNLES];
}Gpt_ConfigType;

/*******************************************************************************
 *                 GLOBAL Variable Extern that in GPT_PBcfg                    *
 *******************************************************************************/

extern const Gpt_ConfigType Gpt_ConfigPtr;


#endif /* GPT_PBCFG_H_ */
