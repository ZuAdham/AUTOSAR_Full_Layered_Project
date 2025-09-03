/******************************************************************************
 *
 * Module: Port
 *
 * File Name: Port.c
 *
 * Description: Source file for TM4C123GH6PM Microcontroller - Port Driver.
 *
 * Author: Adham Muhammed
 ******************************************************************************/
#include "Port_Private.h"

#if(PORT_DEV_ERROR_DETECT==STD_ON)

/*if Dev error is enabled for PORT include the DET module*/
#include "Det.h"

/* AUTOSAR Version checking between DET and Port Modules */
#if ((DET_AR_MAJOR_VERSION != PORT_AR_RELEASE_MAJOR_VERSION)\
        || (DET_AR_MINOR_VERSION != PORT_AR_RELEASE_MINOR_VERSION)\
        || (DET_AR_PATCH_VERSION != PORT_AR_RELEASE_PATCH_VERSION))
#error "The AR version of Det.h does not match the expected version"
#endif

#endif

STATIC const Pin_ConfigType *Port_pinConfig = NULL_PTR;
STATIC uint8 Port_Status = PORT_NOT_INITIALIZED;

/************************************************************************************
 * Service Name      : Port_Init
 * Service ID[hex]   : 0x00
 * Sync/Async        : Synchronous
 * Reentrancy        : Non Reentrant
 * Parameters (in)   : ConfigPtr - Pointer to post-build configuration data
 * Parameters (inout): None
 * Parameters (out)  : None
 * Return value      : None
 * Description       : Initializes the Port Driver module.
 ************************************************************************************/
void Port_Init( const Port_ConfigType* ConfigPtr)
{
    boolean error=FALSE;
#if(PORT_DEV_ERROR_DETECT==STD_ON)

    /* check if the input configuration pointer is not a NULL_PTR */
    if(ConfigPtr==NULL_PTR)
    {
        Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID,
                        PORT_INIT_SID, PORT_E_PARAM_CONFIG);
        error=TRUE;
    }
    else
    {
        /* No Action Required*/
    }
#endif
    if(error==FALSE)
    {
        uint8 i=0;                                  /* Counter to loop on the configured pins*/
        volatile uint32 * PortGpio_Ptr = NULL_PTR;  /* point to the required Port Registers base address */
        /*
         * Set the module state to initialized and point to the PB configuration structure using a global pointer.
         * This global pointer is global to be used by other functions to read the PB configuration structures
         */
        Port_pinConfig=ConfigPtr->pins_config;

        for(i=0;i<PORT_CONFIGURED_CHANNLES;i++)
        {
            switch(Port_pinConfig[i].port_id)
            {
            case  PORTA_ID:
                PortGpio_Ptr = (volatile uint32 *)GPIO_PORTA_BASE_ADDRESS; /* PORTA Base Address */
                break;
            case  PORTB_ID:
                PortGpio_Ptr = (volatile uint32 *)GPIO_PORTB_BASE_ADDRESS; /* PORTB Base Address */
                break;
            case  PORTC_ID:
                PortGpio_Ptr = (volatile uint32 *)GPIO_PORTC_BASE_ADDRESS; /* PORTC Base Address */
                break;
            case  PORTD_ID:
                PortGpio_Ptr = (volatile uint32 *)GPIO_PORTD_BASE_ADDRESS; /* PORTD Base Address */
                break;
            case  PORTE_ID:
                PortGpio_Ptr = (volatile uint32 *)GPIO_PORTE_BASE_ADDRESS; /* PORTE Base Address */
                break;
            case  PORTF_ID:
                PortGpio_Ptr = (volatile uint32 *)GPIO_PORTF_BASE_ADDRESS; /* PORTF Base Address */
                break;
            default:
                break;
            }
            /*PD7 OR PF0*/
            if( ( (Port_pinConfig[i].port_id==PORTD_ID) && (Port_pinConfig[i].pin_id==PORT_PIN_7_ID) ) || (  (Port_pinConfig[i].port_id==PORTF_ID) && (Port_pinConfig[i].pin_id==PORT_PIN_0_ID) ) )
            {
                *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_LOCK_REG_OFFSET) = 0x4C4F434B;                           /* Unlock the GPIOCR register */
                SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_COMMIT_REG_OFFSET) , Port_pinConfig[i].pin_id);  /* Set the corresponding bit in GPIOCR register to allow changes on this pin */

            }
            /*PC0 to PC3*/
            else if( (Port_pinConfig[i].port_id==PORTC_ID) && (Port_pinConfig[i].pin_id<=PORT_PIN_3_ID) )
            {
                /*Do Nothing ... this is JTAG pins*/
                continue;
            }
            else
            {
                /*Do Nothing ... No need to unlock the commit register for this pin*/
            }
            /* in case output pin lets give it`s own initial value*/
            if(Port_pinConfig[i].pin_direction==PORT_PIN_OUT)
            {
                /* Set the corresponding bit in the GPIODIR register to configure it as output pin */
                SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIR_REG_OFFSET) , Port_pinConfig[i].pin_id);
                if(Port_pinConfig[i].pin_levelValue==PORT_PIN_LEVEL_HIGH)
                {
                    /* Set the corresponding bit in the GPIODATA register to provide initial value 1 */
                    SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DATA_REG_OFFSET) , Port_pinConfig[i].pin_id);
                }
                else if(Port_pinConfig[i].pin_levelValue==PORT_PIN_LEVEL_LOW)
                {
                    /* Clear the corresponding bit in the GPIODATA register to provide initial value 1 */
                    CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DATA_REG_OFFSET) , Port_pinConfig[i].pin_id);
                }
                else
                {
                    /*No Action Required*/
                }
            }
            /* in case input pins lets handler the internal resistor*/
            else if(Port_pinConfig[i].pin_direction==PORT_PIN_IN)
            {
                /* Clear the corresponding bit in the GPIODIR register to configure it as Input pin */
                CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIR_REG_OFFSET) , Port_pinConfig[i].pin_id);
                if(Port_pinConfig[i].port_internalResistor==PORT_PIN_INTERNAL_RESISTOR_PULL_UP)
                {
                    /* Set the corresponding bit in the GPIOPUR register to enable the internal pull up pin */
                    SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_PULL_UP_REG_OFFSET) , Port_pinConfig[i].pin_id);
                }
                else if(Port_pinConfig[i].port_internalResistor==PORT_PIN_INTERNAL_RESISTOR_PULL_DOWN)
                {
                    /* Set the corresponding bit in the GPIOPDR register to enable the internal pull down pin */
                    SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_PULL_DOWN_REG_OFFSET) , Port_pinConfig[i].pin_id);
                }
                else if(Port_pinConfig[i].port_internalResistor==PORT_PIN_INTERNAL_RESISTOR_OFF)
                {
                    /* Clear the corresponding bit in the GPIOPUR register to disable the internal pull up pin */
                    CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_PULL_UP_REG_OFFSET) , Port_pinConfig[i].pin_id);

                    /* Clear the corresponding bit in the GPIOPDR register to disable the internal pull down pin */
                    CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_PULL_DOWN_REG_OFFSET) , Port_pinConfig[i].pin_id);
                }
                else
                {
                    /* No Action Required*/
                }
            }
            else
            {
                /*No Action Required*/
            }
            /* Setup the pin mode */
            if(Port_pinConfig[i].pin_mode==PORT_PIN_MODE_DIO)                   /* In case GPIO Mode*/
            {
                /* Set the corresponding bit in the GPIODEN register to Choose digital Enable on this pin  */
                SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET) , Port_pinConfig[i].pin_id);

                /* Clear the corresponding bit in the GPIOAMSEL register to Choose Analog disable on this pin  */
                CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET) , Port_pinConfig[i].pin_id);

                /* Clear the corresponding bit in the GPIOAFSEL register to use it pin as GPIO*/
                CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET) , Port_pinConfig[i].pin_id);

                /* Clear the PMCx bits for this pin */
                *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) &= ~(0x0000000F << ( (Port_pinConfig[i].pin_id)  * 4));
            }
            else if (Port_pinConfig[i].pin_mode==PORT_PIN_MODE_ANALOG)          /* In case Analog Mode*/
            {
                /* Clear the corresponding bit in the GPIODEN register to Choose digital disable on this pin  */
                CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET) , Port_pinConfig[i].pin_id);

                /* Clear the corresponding bit in the GPIOAMSEL register to Choose Analog Enable on this pin  */
                SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET) , Port_pinConfig[i].pin_id);

                /* Set the corresponding bit in the GPIOAFSEL register to use it pin as associated peripheral*/
                SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET) , Port_pinConfig[i].pin_id);

                /* Clear the PMCx bits for this pin */
                *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) &= ~(0x0000000F << ( (Port_pinConfig[i].pin_id)  * 4));
            }
            else        /*any other modes*/
            {
                /* Set the corresponding bit in the GPIODEN register to Choose digital Enable on this pin  */
                SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET) , Port_pinConfig[i].pin_id);

                /* Set the corresponding bit in the GPIOAFSEL register to use it pin as associated peripheral*/
                SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET) , Port_pinConfig[i].pin_id);
            }
            /* Put the mode number inside the corresponding 4 bits of the PMCx bits for this pin */
            /*This line of code may appear quite complex at first glance. so lets try to break it down*/

            *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) &= ~(0x0000000F << ( (Port_pinConfig[i].pin_id)  * 4)) | (Port_pinConfig[i].pin_mode << ( (Port_pinConfig[i].pin_id) * 4));

            /* Port_pinConfig[i].pin_id:
             * Refers to the pin ID from the configuration structure for the current pin being configured.
             */

            /* (0x0000000F << (Port_pinConfig[i].pin_id) * 4):
             * Shifts a mask (0x0000000F, representing 4 bits) left by (pin_id * 4) bits.
             * This is used to create a bit mask that isolates the configuration bits for the specific pin.
             */

            /* ~(0x0000000F << (Port_pinConfig[i].pin_id) * 4):
             * Negates the bit mask, effectively clearing the configuration bits for the specific pin.
             */

            /* Port_pinConfig[i].pin_mode:
             * Retrieves the desired mode for the pin from the pin configuration structure.
             */

            /* (Port_pinConfig[i].pin_mode << (Port_pinConfig[i].pin_id) * 4):
             * Shifts the pin mode value left by (pin_id * 4) bits.
             * This positions the mode bits in the correct location within the register.
             */

            /* &= ~(0x0000000F << (Port_pinConfig[i].pin_id) * 4):
             * Performs a bitwise AND operation with the negated bit mask to clear the corresponding bits.
             * This ensures that only the configuration bits for the specific pin will be affected.
             */

            /* | (Port_pinConfig[i].pin_mode << (Port_pinConfig[i].pin_id) * 4):
             * Performs a bitwise OR operation to set the configuration bits to the desired mode.
             * This combines the cleared bits (from the negated mask) with the shifted pin mode value.
             */

            /* Overall, this line of code updates the configuration of a specific GPIO pin by clearing
             * the relevant bits in the control register and then setting them to the desired mode.
             */

        }/*end of loop*/
        /*Change Port Driver State*/
        Port_Status=PORT_INITIALIZED;
    }
    else
    {
        /*No Action Required*/
    }
}/*end of port_Init()*/

/************************************************************************************
 * Service Name      : Port_SetPinDirection
 * Service ID[hex]   : 0x01
 * Sync/Async        : Synchronous
 * Reentrancy        : Reentrant
 * Parameters (in)   : pin  (Port Pin ID number)
                       Direction (Port Pin Direction )
 * Parameters (inout): None
 * Parameters (out)  : None
 * Return value      : None
 * Description       : Sets the port pin direction
 ************************************************************************************/
#if(PORT_SET_PIN_DIRECTION_API==STD_ON)

void Port_SetPinDirection(Port_PinType Pin, Port_PinDirectionType Direction)
{
    boolean error=FALSE;
#if(PORT_DEV_ERROR_DETECT==STD_ON)
    /* Check if the Driver is initialized before using this function */
    if(Port_Status == PORT_NOT_INITIALIZED)
    {
        Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID,
                        PORT_SET_PIN_DIRECTION_SID, PORT_E_UNINIT);
        error = TRUE;
    }
    else
    {
        /* No Action Required */
    }
    /* Check if the used channel is within the valid range */
    if(PORT_CONFIGURED_CHANNLES<=Pin)
    {
        Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID,
                        PORT_SET_PIN_DIRECTION_SID, PORT_E_PARAM_PIN);
        error = TRUE;
    }
    else
    {
        /* No Action Required */
    }
    /* Check if the used channel is allowed to change its direction during the runtime*/
    if(Port_pinConfig[Pin].port_pinDirectionChangeable==STD_OFF)
    {
        Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID,
                        PORT_SET_PIN_DIRECTION_SID, PORT_E_DIRECTION_UNCHANGEABLE);
        error = TRUE;
    }
    else
    {
        /* No Action Required */
    }
#endif
    /* In-case there are no errors */
    if(error==FALSE)
    {
        if( (Port_pinConfig[Pin].port_id==PORTC_ID) && (Port_pinConfig[Pin].pin_id<=PORT_PIN_3_ID) )
        {
            /*Do Nothing ... this is JTAG pins*/
        }
        else
        {
            volatile uint32 * PortGpio_Ptr = NULL_PTR;  /* point to the required Port Registers base address */
            switch(Port_pinConfig[Pin].port_id)
            {
            case  PORTA_ID:
                PortGpio_Ptr = (volatile uint32 *)GPIO_PORTA_BASE_ADDRESS; /* PORTA Base Address */
                break;
            case  PORTB_ID:
                PortGpio_Ptr = (volatile uint32 *)GPIO_PORTB_BASE_ADDRESS; /* PORTB Base Address */
                break;
            case  PORTC_ID:
                PortGpio_Ptr = (volatile uint32 *)GPIO_PORTC_BASE_ADDRESS; /* PORTC Base Address */
                break;
            case  PORTD_ID:
                PortGpio_Ptr = (volatile uint32 *)GPIO_PORTD_BASE_ADDRESS; /* PORTD Base Address */
                break;
            case  PORTE_ID:
                PortGpio_Ptr = (volatile uint32 *)GPIO_PORTE_BASE_ADDRESS; /* PORTE Base Address */
                break;
            case  PORTF_ID:
                PortGpio_Ptr = (volatile uint32 *)GPIO_PORTF_BASE_ADDRESS; /* PORTF Base Address */
                break;
            default:
                break;
            }
            if(Direction==PORT_PIN_OUT)
            {
                /* Set the corresponding bit in the GPIODIR register to configure it as output pin */
                SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIR_REG_OFFSET) , Port_pinConfig[Pin].pin_id);
                if(Port_pinConfig[Pin].pin_levelValue==PORT_PIN_LEVEL_HIGH)
                {
                    /* Set the corresponding bit in the GPIODATA register to provide initial value 1 */
                    SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DATA_REG_OFFSET) , Port_pinConfig[Pin].pin_id);
                }
                else if(Port_pinConfig[Pin].pin_levelValue==PORT_PIN_LEVEL_LOW)
                {
                    /* Clear the corresponding bit in the GPIODATA register to provide initial value 1 */
                    CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DATA_REG_OFFSET) , Port_pinConfig[Pin].pin_id);
                }
                else
                {
                    /*No Action Required*/
                }
            }
            else if(Direction==PORT_PIN_IN)
            {
                /* Clear the corresponding bit in the GPIODIR register to configure it as Input pin */
                CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIR_REG_OFFSET) , Port_pinConfig[Pin].pin_id);
                if(Port_pinConfig[Pin].port_internalResistor==PORT_PIN_INTERNAL_RESISTOR_PULL_UP)
                {
                    /* Set the corresponding bit in the GPIOPUR register to enable the internal pull up pin */
                    SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_PULL_UP_REG_OFFSET) , Port_pinConfig[Pin].pin_id);
                }
                else if(Port_pinConfig[Pin].port_internalResistor==PORT_PIN_INTERNAL_RESISTOR_PULL_DOWN)
                {
                    /* Set the corresponding bit in the GPIOPDR register to enable the internal pull down pin */
                    SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_PULL_DOWN_REG_OFFSET) , Port_pinConfig[Pin].pin_id);
                }
                else if(Port_pinConfig[Pin].port_internalResistor==PORT_PIN_INTERNAL_RESISTOR_OFF)
                {
                    /* Clear the corresponding bit in the GPIOPUR register to disable the internal pull up pin */
                    CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_PULL_UP_REG_OFFSET) , Port_pinConfig[Pin].pin_id);

                    /* Clear the corresponding bit in the GPIOPDR register to disable the internal pull down pin */
                    CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_PULL_DOWN_REG_OFFSET) , Port_pinConfig[Pin].pin_id);
                }
                else
                {
                    /* No Action Required*/
                }
            }
        }
    }
    else
    {
        /*No Action Required*/
    }
}
#endif

/************************************************************************************
 * Service Name      : Port_RefreshPortDirection
 * Service ID[hex]   : 0x02
 * Sync/Async        : Synchronous
 * Reentrancy        : Non Reentrant
 * Parameters (in)   : None
 * Parameters (inout): None
 * Parameters (out)  : None
 * Return value      : None
 * Description       : Refreshes port direction.
 ************************************************************************************/
void Port_RefreshPortDirection(void)
{
    boolean error=FALSE;
#if(PORT_DEV_ERROR_DETECT==STD_ON)
    /* Check if the Driver is initialized before using this function */
    if(Port_Status == PORT_NOT_INITIALIZED)
    {
        Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID,
                        PORT_REFRESH_Port_DIRECTION_SID, PORT_E_UNINIT);
        error = TRUE;
    }
    else
    {
        /* No Action Required */
    }
#endif
    if(error==FALSE)
    {
        uint8 i=0;                                  /* Counter to loop on the configured pins*/
        volatile uint32 * PortGpio_Ptr = NULL_PTR;  /* point to the required Port Registers base address */

        for(i=0;i<PORT_CONFIGURED_CHANNLES;i++)
        {
            if( (Port_pinConfig[i].port_id==PORTC_ID) && (Port_pinConfig[i].pin_id<=PORT_PIN_3_ID) )
            {
                /*Do Nothing ... this is JTAG pins*/
            }
            else
            {
                switch(Port_pinConfig[i].port_id)
                {
                case  PORTA_ID:
                    PortGpio_Ptr = (volatile uint32 *)GPIO_PORTA_BASE_ADDRESS; /* PORTA Base Address */
                    break;
                case  PORTB_ID:
                    PortGpio_Ptr = (volatile uint32 *)GPIO_PORTB_BASE_ADDRESS; /* PORTB Base Address */
                    break;
                case  PORTC_ID:
                    PortGpio_Ptr = (volatile uint32 *)GPIO_PORTC_BASE_ADDRESS; /* PORTC Base Address */
                    break;
                case  PORTD_ID:
                    PortGpio_Ptr = (volatile uint32 *)GPIO_PORTD_BASE_ADDRESS; /* PORTD Base Address */
                    break;
                case  PORTE_ID:
                    PortGpio_Ptr = (volatile uint32 *)GPIO_PORTE_BASE_ADDRESS; /* PORTE Base Address */
                    break;
                case  PORTF_ID:
                    PortGpio_Ptr = (volatile uint32 *)GPIO_PORTF_BASE_ADDRESS; /* PORTF Base Address */
                    break;
                default:
                    break;
                }
                /* PORT060: The function Port_RefreshPortDirection shall refresh the direction of all configured ports to the configured direction (PortPinDirection).
               PORT061: The function Port_RefreshPortDirection shall exclude those port pins from refreshing that are configured as �pin direction changeable during runtime
                 */
                if( (Port_pinConfig[i].pin_direction==PORT_PIN_OUT) && (Port_pinConfig[i].port_pinDirectionChangeable==STD_OFF) )
                {
                    /* Set the corresponding bit in the GPIODIR register to configure it as output pin */
                    SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIR_REG_OFFSET) , Port_pinConfig[i].pin_id);
                }
                else if((Port_pinConfig[i].pin_direction==PORT_PIN_IN) && (Port_pinConfig[i].port_pinDirectionChangeable==STD_OFF) )
                {
                    /* Clear the corresponding bit in the GPIODIR register to configure it as Input pin */
                    CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIR_REG_OFFSET) , Port_pinConfig[i].pin_id);
                }
                else
                {
                    /*this mean that Port_pinDirection is changeable on this pin and according to requirement:
                 [PORT061] we exclude those port pins from refreshing that are configured as pin direction changeable during runtime*/
                }

            }
        }
    }
}
/************************************************************************************
 * Service Name      : Port_GetVersionInfo
 * Service ID[hex]   : 0x03
 * Sync/Async        : Synchronous
 * Reentrancy        : Non Reentrant
 * Parameters (in)   : None
 * Parameters (inout): None
 * Parameters (out)  : versioninfo (pointer to where to store the version information of this module.)
 * Return value      : None
 * Description       : Returns the version information of this module.
 ************************************************************************************/
#if(PORT_VERSION_INFO_API==STD_ON)
void Port_GetVersionInfo(Std_VersionInfoType* versioninfo)
{
#if(PORT_DEV_ERROR_DETECT==STD_ON)
    /* Check if the Driver is initialized before using this function */
    if(Port_Status == PORT_NOT_INITIALIZED)
    {
        Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID,
                        PORT_GET_VERSION_INFO_SID, PORT_E_UNINIT);
    }
    else
    {
        /* No Action Required */
    }
    /* Check if the versioninfo is Null before using this function */
    if(versioninfo==NULL_PTR)
    {
        Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID,
                        PORT_GET_VERSION_INFO_SID, PORT_E_PARAM_POINTER);
    }
    else
    {
        /* No Action Required*/
    }
#endif
    /* Copy the vendor Id */
    versioninfo->vendorID = (uint16)PORT_VENDOR_ID;
    /* Copy the module Id */
    versioninfo->moduleID = (uint16)PORT_MODULE_ID;
    /* Copy Software Major Version */
    versioninfo->sw_major_version = (uint8)PORT_SW_MAJOR_VERSION;
    /* Copy Software Minor Version */
    versioninfo->sw_minor_version = (uint8)PORT_SW_MINOR_VERSION;
    /* Copy Software Patch Version */
    versioninfo->sw_patch_version = (uint8)PORT_SW_PATCH_VERSION;
}
#endif

/************************************************************************************
 * Service Name      : Port_SetPinMode
 * Service ID[hex]   : 0x04
 * Sync/Async        : Synchronous
 * Reentrancy        : Reentrant
 * Parameters (in)   : Pin (Port Pin ID number)
                       Mode (New Port Pin mode to be set on port pin.)
 * Parameters (inout): None
 * Parameters (out)  : None
 * Return value      : None
 * Description       : Sets the port pin mode
 ************************************************************************************/
#if(PORT_SET_PIN_MODE_API==STD_ON)
void Port_SetPinMode(Port_PinType Pin,Port_PinModeType Mode)
{
    boolean error=FALSE;
#if(PORT_DEV_ERROR_DETECT==STD_ON)
    /* Check if the Driver is initialized before using this function */
    if( Port_Status == PORT_NOT_INITIALIZED)
    {
        Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID,
                        PORT_SET_PIN_MODE_SID, PORT_E_UNINIT);
        error = TRUE;
    }
    else
    {
        /* No Action Required */
    }
    /* Check if the used channel is within the valid range */
    if(PORT_CONFIGURED_CHANNLES<=Pin)
    {
        Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID,
                        PORT_SET_PIN_MODE_SID, PORT_E_PARAM_PIN);
        error = TRUE;
    }
    else
    {
        /* No Action Required */
    }
    /* Check if the used channel is allowed to change its mode during the runtime*/
    if(Port_pinConfig[Pin].port_pinModeChangeable == STD_OFF)
    {
        Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID,
                        PORT_SET_PIN_MODE_SID, PORT_E_MODE_UNCHANGEABLE);
        error=TRUE;
    }
    else
    {
        /*No Action Required*/
    }
#endif
    if(error==FALSE)
    {
        if( (Port_pinConfig[Pin].port_id==PORTC_ID) && (Port_pinConfig[Pin].pin_id<=PORT_PIN_3_ID) )
        {
            /*Do Nothing ... this is JTAG pins*/
        }
        else
        {
            volatile uint32 * PortGpio_Ptr = NULL_PTR;  /* point to the required Port Registers base address */

            switch(Port_pinConfig[Pin].port_id)
            {
            case  PORTA_ID:
                PortGpio_Ptr = (volatile uint32 *)GPIO_PORTA_BASE_ADDRESS; /* PORTA Base Address */
                break;
            case  PORTB_ID:
                PortGpio_Ptr = (volatile uint32 *)GPIO_PORTB_BASE_ADDRESS; /* PORTB Base Address */
                break;
            case  PORTC_ID:
                PortGpio_Ptr = (volatile uint32 *)GPIO_PORTC_BASE_ADDRESS; /* PORTC Base Address */
                break;
            case  PORTD_ID:
                PortGpio_Ptr = (volatile uint32 *)GPIO_PORTD_BASE_ADDRESS; /* PORTD Base Address */
                break;
            case  PORTE_ID:
                PortGpio_Ptr = (volatile uint32 *)GPIO_PORTE_BASE_ADDRESS; /* PORTE Base Address */
                break;
            case  PORTF_ID:
                PortGpio_Ptr = (volatile uint32 *)GPIO_PORTF_BASE_ADDRESS; /* PORTF Base Address */
                break;
            default:
                break;
            }
            /* Setup the pin mode */
            if(Port_pinConfig[Pin].pin_mode==PORT_PIN_MODE_DIO)                   /* In case GPIO Mode*/
            {
                /* Set the corresponding bit in the GPIODEN register to Choose digital Enable on this pin  */
                SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET) , Port_pinConfig[Pin].pin_id);

                /* Clear the corresponding bit in the GPIOAMSEL register to Choose Analog disable on this pin  */
                CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET) , Port_pinConfig[Pin].pin_id);

                /* Clear the corresponding bit in the GPIOAFSEL register to use it pin as GPIO*/
                CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET) , Port_pinConfig[Pin].pin_id);

                /* Clear the PMCx bits for this pin  */
                *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) &= ~(0x0000000F << ((Port_pinConfig[Pin].pin_id) * 4));
            }
            else if (Port_pinConfig[Pin].pin_mode==PORT_PIN_MODE_ANALOG)          /* In case Analog Mode*/
            {
                /* Clear the corresponding bit in the GPIODEN register to Choose digital disable on this pin  */
                CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET) , Port_pinConfig[Pin].pin_id);

                /* Clear the corresponding bit in the GPIOAMSEL register to Choose Analog Enable on this pin  */
                SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET) , Port_pinConfig[Pin].pin_id);

                /* Set the corresponding bit in the GPIOAFSEL register to use it pin as associated peripheral*/
                SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET) , Port_pinConfig[Pin].pin_id);

                /* Clear the PMCx bits for this pin  */
                *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) &= ~(0x0000000F << ((Port_pinConfig[Pin].pin_id) * 4));
            }
            else        /*any other modes*/
            {
                /* Set the corresponding bit in the GPIODEN register to Choose digital Enable on this pin  */
                SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET) , Port_pinConfig[Pin].pin_id);

                /* Set the corresponding bit in the GPIOAFSEL register to use it pin as associated peripheral*/
                SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET) , Port_pinConfig[Pin].pin_id);

                /* Put the mode number inside the corresponding 4 bits of the PMCx bits for this pin */
                *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) &= ~(0x0000000F << ( (Port_pinConfig[Pin].pin_id)  * 4)) | (Port_pinConfig[Pin].pin_mode << ( (Port_pinConfig[Pin].pin_id) * 4));
            }
        }
    }
    else
    {
        /*No Action Required*/
    }
}
#endif
