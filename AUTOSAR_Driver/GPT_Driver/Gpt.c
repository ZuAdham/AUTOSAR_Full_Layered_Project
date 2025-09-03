/******************************************************************************
 *
 * Module: Gpt
 *
 * File Name: Gpt.c
 *
 * Description: Source file for TM4C123GH6PM Microcontroller - GPT Timer Driver.
 *
 * Author: Adham Muhammed
 ******************************************************************************/
#include "Gpt_Private.h"

#if(GPT_DEV_ERROR_DETECT==STD_ON)

/*if Dev error is enabled for GPT include the DET module*/
#include "Det.h"

/* AUTOSAR Version checking between DET and GPT Modules */
#if ((DET_AR_MAJOR_VERSION != GPT_AR_RELEASE_MAJOR_VERSION)\
        || (DET_AR_MINOR_VERSION != GPT_AR_RELEASE_MINOR_VERSION)\
        || (DET_AR_PATCH_VERSION != GPT_AR_RELEASE_PATCH_VERSION))
#error "The AR version of Det.h does not match the expected version"
#endif

#endif

STATIC const Gpt_ConfigChannel * Gpt_Configuration = NULL_PTR;

/* this array of struc to hold dynamic configuration as state / interrupt state / wakeup_state */
STATIC Gpt_DynamicConfigType Gpt_dynamicConfiguration[GPT_CONFIGURED_CHANNLES];

/*this array of pointer to function to hold the address of Callback Function*/
void (*GptNotification[GPT_CONFIGURED_CHANNLES]) (void)={NULL_PTR};
STATIC uint8 Gpt_Status = GPT_NOT_INITIALIZED;

/************************************************************************************
 * Service name          : Gpt_Init
 * Service ID[hex]       : 0x01
 * Sync/Async            : Synchronous
 * Reentrancy            : Non Reentrant
 * Parameters (in)       : ConfigPtr (Pointer to a selected configuration structure)
 * Parameters (inout)    : None
 * Parameters (out)      : None
 * Return value          : None
 * Description           : Initializes the hardware timer module.
 ************************************************************************************/
void Gpt_Init(const Gpt_ConfigType* ConfigPtr)
{
    boolean error = FALSE;
    uint8 i=0;
#if(GPT_DEV_ERROR_DETECT==STD_ON)
    /* check if the input configuration pointer is not a NULL_PTR */
    if (NULL_PTR == ConfigPtr)
    {
        Det_ReportError(GPT_MODULE_ID, GPT_INSTANCE_ID,
                        GPT_INIT_SID,GPT_E_PARAM_POINTER);
        error=TRUE;
    }
    else
    {
        /* No Action Required */
    }
    /* check of the GPT status is already Initialized*/
    if(Gpt_Status==GPT_INITIALIZED)
    {
        Det_ReportError(GPT_MODULE_ID, GPT_INSTANCE_ID,
                        GPT_INIT_SID,GPT_E_ALREADY_INITIALIZED);
        error=TRUE;
    }
    else
    {
        /* No Action Required */
    }
#endif
    /*No development error detected or may the dev error is disabled*/
    if(FALSE == error)
    {
        /*
         * Set the module state to initialized and point to the PB configuration structure using a global pointer.
         * This global pointer is global to be used by other functions to read the PB configuration structures
         */
        Gpt_Status= GPT_INITIALIZED;
        Gpt_Configuration= ConfigPtr->Gpt_Channels;      /* address of the first Channels structure --> Channels[0] */

        /* In the next enhancement, we could integrate Tiva-C Timers, allowing us to configure multiple timers for increased functionality. */
        for(i = 0 ; i <GPT_CONFIGURED_CHANNLES; i++)
        {
            GptNotification[i]=Gpt_Configuration->GptNotifcation;

            switch (Gpt_Configuration[i].GptChannelId)
            {
            case SYSTICK_TIMER:

                /* disable the timer */
                SYSTICK_CTRL_REG= 0;

                /* clear current ticks */
                SYSTICK_CURRENT_REG = 0;

                /* set clock source to System Clock */
                SET_BIT(SYSTICK_CTRL_REG, CLK_SRC);

                /* disable SysTick interrupts */
                CLEAR_BIT(SYSTICK_CTRL_REG, INTEN_SYSTICK);

                /* disable systick timer interrupt at NVIC */
                CLEAR_BIT(NVIC_EN0_REG ,INTEN_NVIC);

                break;
                /* In the next enhancement, we could integrate Tiva-C Timers, so we could add more timer id and more switch-case */
            default :
                break;
            }
            /*open chapter 7 functional requirement to understand the state diagram of Timer*/
            Gpt_dynamicConfiguration[i].gpt_channel_state=INITIALIZED;

            /*Note the init function is not resposible for Enable The Interrupts for timer channel as mentioned in SWS requirement {GPT107] */
            Gpt_dynamicConfiguration[i].Gpt_EnableChannelNotification=INTERRUPT_OFF;

            Gpt_dynamicConfiguration[i].gpt_wakeup_state=INTERRUPT_OFF;
        }   /*end of for loop*/
    }
    else
    {
        /* No Action Required */
    }
}

/************************************************************************************
 * Service Name          : Gpt_DeInit
 * Service ID[hex]       : 0x02
 * Sync/Async            : Synchronous
 * Reentrancy            : Non Reentrant
 * Parameters (in)       : None
 * Parameters (inout)    : None
 * Parameters (out)      : None
 * Return value          : None
 * Description           : Deinitializes all hardware timer channels.
 ************************************************************************************/
#if(GPT_DEINIT_API==STD_ON)
void Gpt_DeInit(void)
{
    boolean error = FALSE;
    uint8 i=0;
#if(GPT_DEV_ERROR_DETECT==STD_ON)
    if(Gpt_Status==GPT_NOT_INITIALIZED)
    {
        Det_ReportError(GPT_MODULE_ID, GPT_INSTANCE_ID,
                        GPT_DEINIT_SID,GPT_E_UNINIT);
        error=TRUE;
    }
    else
    {
        /* No Action Required */
    }
    for(i = 0 ; i <GPT_CONFIGURED_CHANNLES; i++)
    {
        if(Gpt_dynamicConfiguration[i].gpt_channel_state==RUNNING)
        {
            Det_ReportError(GPT_MODULE_ID, GPT_INSTANCE_ID,
                            GPT_DEINIT_SID,GPT_E_BUSY);
            error=TRUE;
            break;       /*Just report error one time*/
        }
        else
        {
            /* No Action Required */
        }
    }
#endif
    /*No development error detected or may the dev error is disabled*/
    if(error==FALSE)
    {
        Gpt_Status= GPT_NOT_INITIALIZED;
        /* In the next enhancement, we could integrate Tiva-C Timers, allowing us to configure multiple timers for increased functionality. */
        for(i = 0 ; i <GPT_CONFIGURED_CHANNLES; i++)
        {
            switch (Gpt_Configuration[i].GptChannelId)
            {
            case SYSTICK_TIMER:

                /* disable the timer */
                CLEAR_BIT(SYSTICK_CTRL_REG, ENABLE);

                /* clear current ticks */
                SYSTICK_CURRENT_REG = 0;

                /* disable SysTick interrupts */
                CLEAR_BIT(SYSTICK_CTRL_REG, INTEN_SYSTICK);

                /* disable systick timer interrupt at NVIC */
                CLEAR_BIT(NVIC_EN0_REG ,INTEN_NVIC);

                break;
                /* In the next enhancement, we could integrate Tiva-C  Timers, so we could add more timer id and more switch-case */
            default :
                break;
            }
            Gpt_dynamicConfiguration[i].gpt_channel_state=INITIALIZED;
            Gpt_dynamicConfiguration[i].Gpt_EnableChannelNotification=INTERRUPT_OFF;
            Gpt_dynamicConfiguration[i].gpt_wakeup_state=INTERRUPT_OFF;
        }
    }
    else
    {
        /* No Action Required */
    }
}
#endif

/************************************************************************************
 * Service Name      : Gpt_GetTimeElapsed
 * Service ID[hex]   : 0x03
 * Sync/Async        : Synchronous
 * Reentrancy        : Reentrant
 * Parameters (in)   : Channel (Numeric identifier of the GPT channel.)
 * Parameters (inout): None
 * Parameters (out)  : None
 * Return value      : Gpt_ValueType (Elapsed timer value (in number of ticks))
 * Description       : Returns the time already elapsed.
 ************************************************************************************/
#if(GPT_TIME_ELAPSED_API==STD_ON)
Gpt_ValueType Gpt_GetTimeElapsed(Gpt_ChannelType Channel)
{
    boolean error=FALSE;
    uint64 elapsed_time=0;
#if(GPT_DEV_ERROR_DETECT==STD_ON)
    /* check of the GPT status is already Initialized*/
    if(Gpt_Status==GPT_NOT_INITIALIZED)
    {
        Det_ReportError(GPT_MODULE_ID, GPT_INSTANCE_ID,
                        GPT_GET_TIME_ELAPSED_SID,GPT_E_UNINIT);
        error=TRUE;
    }
    else
    {
        /* No Action Required */
    }
    /* Check if the used channel is within the valid range */
    if(GPT_CONFIGURED_CHANNLES<= Channel)
    {
        Det_ReportError(GPT_MODULE_ID, GPT_INSTANCE_ID,
                        GPT_GET_TIME_ELAPSED_SID,GPT_E_PARAM_CHANNEL);
        error=TRUE;
    }
    else
    {
        /* No Action Required */
    }
#endif
    /*No development error detected or may the dev error is disabled*/
    if(error==FALSE)
    {
        switch (Gpt_Configuration[Channel].GptChannelId)
        {
        case SYSTICK_TIMER:
            elapsed_time= SYSTICK_CURRENT_REG;
            break;
            /* In the next enhancement, we could integrate Tiva-C  Timers, so we could add more timer id and more switch-case */
        default:
            break;
        }
    }
    else
    {
        /* No Action Required */
    }
    return elapsed_time;
}
#endif

/************************************************************************************
 * Service Name      : Gpt_GetTimeRemaining
 * Service ID[hex]   : 0x04
 * Sync/Async        : Synchronous
 * Reentrancy        : Reentrant
 * Parameters (in)   : Channel (Numeric identifier of the GPT channel.)
 * Parameters (inout): None
 * Parameters (out)  : None
 * Return value      : Gpt_ValueType (Remaining timer value (in number of ticks))
 * Description       : Returns the time remaining until the target time is reached
 ************************************************************************************/
#if(GPT_TIME_REMAINING_API==STD_ON)
Gpt_ValueType Gpt_GetTimeRemaining(Gpt_ChannelType Channel)
{
    boolean error=FALSE;
    Gpt_ValueType current_time=0;
    Gpt_ValueType target_time=0;
    Gpt_ValueType remaining_time=0;

#if(GPT_DEV_ERROR_DETECT==STD_ON)
    /* check of the GPT status is already Initialized*/
    if(Gpt_Status==GPT_NOT_INITIALIZED)
    {
        Det_ReportError(GPT_MODULE_ID, GPT_INSTANCE_ID,
                        GPT_TIME_REMAINING_API,GPT_E_UNINIT);
        error=TRUE;
    }
    else
    {
        /* No Action Required */
    }
    /* Check if the used channel is within the valid range */
    if(GPT_CONFIGURED_CHANNLES<= Channel)
    {
        Det_ReportError(GPT_MODULE_ID, GPT_INSTANCE_ID,
                        GPT_TIME_REMAINING_API,GPT_E_PARAM_CHANNEL);
        error=TRUE;
    }
    else
    {
        /* No Action Required */
    }
#endif
    if(error==FALSE)
    {
        if(Gpt_Configuration[Channel].GptChannelMode==GPT_ONE_SHOT && Gpt_dynamicConfiguration[Channel].gpt_channel_state==EXPIRED)
        {
            /* Channel is in one-shot mode and has expired, return 0 */
            remaining_time=0;
        }
        else
        {
            switch (Gpt_Configuration[Channel].GptChannelId)
            {
            case SYSTICK_TIMER:
                current_time= SYSTICK_CURRENT_REG;
                target_time= SYSTICK_RELOAD_REG;
                break;
                /* In the next enhancement, we could integrate Tiva-C  Timers, so we could add more timer id and more switch-case */
            default:
                break;
            }
            /* Calculate the remaining time */
            remaining_time=target_time-current_time;
        }
    }
    else
    {
        /*No Action Required*/
    }
    return remaining_time;
}
#endif

/************************************************************************************
 * Service Name      : Gpt_StartTimer
 * Service ID[hex]   : 0x05
 * Sync/Async        : Synchronous
 * Reentrancy        : Reentrant
 * Parameters (in)   : Channel (Numeric identifier of the GPT channel.)
                       Value (Target time in number of ticks. )
 * Parameters (inout): None
 * Parameters (out)  : None
 * Return value      : None
 * Description       : Starts a timer channel.
 ************************************************************************************/
void Gpt_StartTimer(Gpt_ChannelType Channel, Gpt_ValueType Value)
{
    boolean error=FALSE;
#if(GPT_DEV_ERROR_DETECT==STD_ON)
    /* check of the GPT status is already Initialized*/
    if(Gpt_Status==GPT_NOT_INITIALIZED)
    {
        Det_ReportError(GPT_MODULE_ID, GPT_INSTANCE_ID,
                        GPT_START_TIMER_SID,GPT_E_UNINIT);
        error=TRUE;
    }
    else
    {
        /* No Action Required */
    }
    /* Check if the used channel is within the valid range */
    if(GPT_CONFIGURED_CHANNLES<= Channel)
    {
        Det_ReportError(GPT_MODULE_ID, GPT_INSTANCE_ID,
                        GPT_START_TIMER_SID,GPT_E_PARAM_CHANNEL);
        error=TRUE;
    }
    else
    {
        /* No Action Required */
    }
    /*check if the value exceeding the maximum timer resolution).*/
    if(Value==0)
    {
        Det_ReportError(GPT_MODULE_ID, GPT_INSTANCE_ID,
                        GPT_START_TIMER_SID,GPT_E_PARAM_VALUE);
        error=TRUE;
    }
    else
    {
        /* No Action Required */
    }
    /*Check if the selected channel is already used or not */
    if(Gpt_dynamicConfiguration[Channel].gpt_channel_state==RUNNING)
    {
        Det_ReportError(GPT_MODULE_ID, GPT_INSTANCE_ID,
                        GPT_START_TIMER_SID,GPT_E_BUSY);
        error=TRUE;
    }
    else
    {
        /* No Action Required */
    }
#endif
    /*No development error detected or may the dev error is disabled*/
    if(error==FALSE)
    {
        switch (Gpt_Configuration[Channel].GptChannelId)
        {
        case SYSTICK_TIMER:
            /* set compare value */
            SYSTICK_RELOAD_REG = (Gpt_Configuration[Channel].GptChannelTickFrequency-1)*Value;

            /* Clear the Current Register value */
            SYSTICK_CURRENT_REG = 0;

            /* Assign priority level 1 to the SysTick Interrupt */
            NVIC_SYSTEM_PRI3_REG =  (NVIC_SYSTEM_PRI3_REG & SYSTICK_PRIORITY_MASK) | (SYSTICK_INTERRUPT_PRIORITY << SYSTICK_PRIORITY_BITS_POS);

            /* enable the timer to start counting */
            SET_BIT(SYSTICK_CTRL_REG, ENABLE);
            break;
            /* In the next enhancement, we could integrate Tiva-C  Timers, so we could add more timer id and more switch-case */
        default:
            break;
        }
        /*Change Timer state into Running State*/
        Gpt_dynamicConfiguration[Channel].gpt_channel_state=RUNNING;
    }
    else
    {
        /* No Action Required */
    }
}
/************************************************************************************
 * Service Name      : Gpt_StopTimer
 * Service ID[hex]   : 0x06
 * Sync/Async        : Synchronous
 * Reentrancy        : Reentrant
 * Parameters (in)   : Channel (Numeric identifier of the GPT channel.)
 * Parameters (inout): None
 * Parameters (out)  : None
 * Return value      : None
 * Description       : Stops a timer channel.
 ************************************************************************************/
void Gpt_StopTimer(Gpt_ChannelType Channel)
{
    boolean error=FALSE;
#if(GPT_DEV_ERROR_DETECT==STD_ON)
    /* check of the GPT status is already Initialized*/
    if(Gpt_Status==GPT_NOT_INITIALIZED)
    {
        Det_ReportError(GPT_MODULE_ID, GPT_INSTANCE_ID,
                        GPT_STOP_TIMER_SID,GPT_E_UNINIT);
        error=TRUE;
    }
    else
    {
        /* No Action Required */
    }
    /* Check if the used channel is within the valid range */
    if(GPT_CONFIGURED_CHANNLES<= Channel)
    {
        Det_ReportError(GPT_MODULE_ID, GPT_INSTANCE_ID,
                        GPT_STOP_TIMER_SID,GPT_E_PARAM_CHANNEL);
        error=TRUE;
    }
    else
    {
        /* No Action Required */
    }
#endif
    /*No development error detected or may the dev error is disabled*/
    if(error==FALSE)
    {
        /*If the function Gpt_StopTimer is called on a channel in state "initialized", "stopped" or "expired", the function shall leave without any action (no change of the channel state) */
        if ( ( Gpt_dynamicConfiguration[Channel].gpt_channel_state == INITIALIZED ) || \
                ( Gpt_dynamicConfiguration[Channel].gpt_channel_state ==STOPPED ) || \
                ( Gpt_dynamicConfiguration[Channel].gpt_channel_state == EXPIRED ) )
        {
            return;
        }
        else
        {

        }

        /* get the timer base address */
        switch (Gpt_Configuration[Channel].GptChannelId)
        {
        case SYSTICK_TIMER:

            /* disable the timer */
            CLEAR_BIT(SYSTICK_CTRL_REG, ENABLE);
            break;
            /* In the next enhancement, we could integrate Tiva-C  Timers, so we could add more timer id and more switch-case */
        default:
            break;
        }
        Gpt_dynamicConfiguration[Channel].gpt_channel_state=STOPPED;
    }
    else
    {
        /* No Action Required */
    }
}
/************************************************************************************
 * Service name      : Gpt_EnableNotification
 * Service ID[hex]   : 0x07
 * Sync/Async        : Synchronous
 * Reentrancy        : Reentrant
 * Parameters (in)   : Channel (Numeric identifier of the GPT channel.)
 * Parameters (inout): None
 * Parameters (out)  : None
 * Return value      : None
 * Description       : Enables the interrupt notification for a channel (relevant in normal mode).
 ************************************************************************************/
#if(GPT_ENABLE_DISABLE_NOTIFICATION_API ==STD_ON)
void Gpt_EnableNotification(Gpt_ChannelType Channel)
{
    boolean error =FALSE;
#if(GPT_DEV_ERROR_DETECT==STD_ON)
    /* check of the GPT status is already Initialized*/
    if(Gpt_Status==GPT_NOT_INITIALIZED)
    {
        Det_ReportError(GPT_MODULE_ID, GPT_INSTANCE_ID,
                        GPT_ENABLE_NOTIFICATION_SID,GPT_E_UNINIT);
        error=TRUE;
    }
    else
    {
        /* No Action Required */
    }
    /* Check if the used channel is within the valid range */
    if(GPT_CONFIGURED_CHANNLES<= Channel)
    {
        Det_ReportError(GPT_MODULE_ID, GPT_INSTANCE_ID,
                        GPT_ENABLE_NOTIFICATION_SID,GPT_E_PARAM_CHANNEL);
        error=TRUE;
    }
    else
    {
        /* No Action Required */
    }
    /*Check if no valid notification function is configured (GptNotification)*/
    if (GptNotification[Channel]==NULL_PTR)
    {
        Det_ReportError(GPT_MODULE_ID, GPT_INSTANCE_ID,
                        GPT_ENABLE_NOTIFICATION_SID,GPT_E_PARAM_CHANNEL);
        error=TRUE;
    }
    else
    {
        /* No Action Required */
    }
#endif
    /*No development error detected or may the dev error is disabled*/
    if(error==FALSE)
    {
        switch (Gpt_Configuration[Channel].GptChannelId)
        {
        case SYSTICK_TIMER:

            /* Enable SysTick interrupts */
            SET_BIT(SYSTICK_CTRL_REG, INTEN_SYSTICK);

            /* Enable systick timer interrupt at NVIC */
            SET_BIT(NVIC_EN0_REG ,INTEN_NVIC);
            break;

            /* In the next enhancement, we could integrate Tiva-C  Timers, so we could add more timer id and more switch-case */
        default:
            break;
        }
        Gpt_dynamicConfiguration[Channel].Gpt_EnableChannelNotification = INTERRUPT_ON;
    }
    else
    {
        /* No Action Required */
    }
}
#endif

/************************************************************************************
 * Service name      : Gpt_DisableNotification
 * Service ID[hex]   : 0x08
 * Sync/Async        : Synchronous
 * Reentrancy        : Reentrant
 * Parameters (in)   : Channel (Numeric identifier of the GPT channel)
 * Parameters (inout): None
 * Parameters (out)  : None
 * Return value      : None
 * Description       : Disables the interrupt notification for a channel (relevant in normal mode).
 ************************************************************************************/
#if(GPT_ENABLE_DISABLE_NOTIFICATION_API==STD_ON)
void Gpt_DisableNotification(Gpt_ChannelType Channel)
{
    boolean error = FALSE;
#if(GPT_DEV_ERROR_DETECT==STD_ON)
    /* check of the GPT status is already Initialized*/
    if(Gpt_Status==GPT_NOT_INITIALIZED)
    {
        Det_ReportError(GPT_MODULE_ID, GPT_INSTANCE_ID,
                        GPT_DISABLE_NOTIFICATION_SID,GPT_E_UNINIT);
        error=TRUE;
    }
    else
    {
        /* No Action Required */
    }
    /* Check if the used channel is within the valid range */
    if(GPT_CONFIGURED_CHANNLES<= Channel)
    {
        Det_ReportError(GPT_MODULE_ID, GPT_INSTANCE_ID,
                        GPT_DISABLE_NOTIFICATION_SID,GPT_E_PARAM_CHANNEL);
        error=TRUE;
    }
    else
    {
        /* No Action Required */
    }
    /*Check if no valid notification function is configured (GptNotification)*/
    if (GptNotification[Channel]==NULL_PTR)
    {
        Det_ReportError(GPT_MODULE_ID, GPT_INSTANCE_ID,
                        GPT_DISABLE_NOTIFICATION_SID,GPT_E_PARAM_CHANNEL);
        error=TRUE;
    }
    else
    {
        /* No Action Required */
    }
#endif
    /*No development error detected or may the dev error is disabled*/
    if(FALSE==error)
    {
        switch (Gpt_Configuration[Channel].GptChannelId)
        {
        case SYSTICK_TIMER:

            /* Disable SysTick interrupts */
            CLEAR_BIT(SYSTICK_CTRL_REG, INTEN_SYSTICK);

            /* Diaable systick timer interrupt at NVIC */
            CLEAR_BIT(NVIC_EN0_REG ,INTEN_NVIC);
            break;

            /* In the next enhancement, we could integrate Tiva-C  Timers, so we could add more timer id and more switch-case */
        default:
            break;
        }
        Gpt_dynamicConfiguration[Channel].Gpt_EnableChannelNotification = INTERRUPT_OFF;
    }
    else
    {
        /* No Action Required */
    }
}
#endif
/************************************************************************************
 * Service name      : Gpt_GetVersionInfo
 * Service ID[hex]   : 0x00
 * Sync/Async        : Synchronous
 * Reentrancy        : Reentrant
 * Parameters (in)   : None
 * Parameters (inout): None
 * Parameters (out)  : VersionInfoPtr Pointer to where to store the version information of this module.
 * Return value      : None
 * Description       : Returns the version information of this module.
 ************************************************************************************/
#if (GPT_VERSION_INFO_API == STD_ON)
void Gpt_GetVersionInfo(Std_VersionInfoType* VersionInfoPtr)
{
#if (GPT_DEV_ERROR_DETECT == STD_ON)
    /* Check if input pointer is not Null pointer */
    if(NULL_PTR == VersionInfoPtr)
    {
        /* Report to DET  */
        Det_ReportError(GPT_MODULE_ID, GPT_INSTANCE_ID,
                        GPT_GET_VERSION_INFO_SID, GPT_E_PARAM_POINTER);
    }
    else
#endif /* (GPT_DEV_ERROR_DETECT == STD_ON) */
    {
        /* Copy the vendor Id */
        VersionInfoPtr->vendorID = (uint16)GPT_VENDOR_ID;
        /* Copy the module Id */
        VersionInfoPtr->moduleID = (uint16)GPT_MODULE_ID;
        /* Copy Software Major Version */
        VersionInfoPtr->sw_major_version = (uint8)GPT_SW_MAJOR_VERSION;
        /* Copy Software Minor Version */
        VersionInfoPtr->sw_minor_version = (uint8)GPT_SW_MINOR_VERSION;
        /* Copy Software Patch Version */
        VersionInfoPtr->sw_patch_version = (uint8)GPT_SW_PATCH_VERSION;
    }
}
#endif
