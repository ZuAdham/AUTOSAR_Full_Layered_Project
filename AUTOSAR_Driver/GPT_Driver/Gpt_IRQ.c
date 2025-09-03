 /******************************************************************************
 *
 * Module: Gpt
 *
 * File Name: Gpt_IRQ.c
 *
 * Description: Source file for TM4C123GH6PM Microcontroller Handlers - GPT Timer Driver.
 *
 * Author: Adham Muhammed
 ******************************************************************************/
#include"Gpt_Private.h"

/*Array of Pointer to Functions used to point upper layer functions*/
extern void (*GptNotification[GPT_CONFIGURED_CHANNLES]) (void);

/*Note In future releases, additional timer handlers may be added for enhanced functionality.
*       Developers should remember to:
*       1. Declare an external prototype of this ISR in the startup code.
*       2. Add the address of this ISR to the interrupt vector table.
*/

/********************************************************************************************************
* Service Name: SysTick_Handler
* Description: SysTick Timer ISR
* brief of Handler : Checks if there is a notification function registered for the SysTick timer (SYSTICK_TIMER).
*                    If a notification function is registered, it calls the function.
*                    Note: The trigger flag (COUNT) bit is automatically cleared by the hardware.
*                    If no notification function is registered, it does nothing.
*********************************************************************************************************/
void SysTick_Handler(void)
{
  if(GptNotification[SYSTICK_TIMER] != NULL_PTR)
  {
    GptNotification[SYSTICK_TIMER]();
    /* No need to clear the trigger flag (COUNT) bit ... it cleared automatically by the HW */
  }
  else
  {
    /* Do Nothing */
  }
}
