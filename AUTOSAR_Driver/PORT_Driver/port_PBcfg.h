/******************************************************************************
 *
 * Module: Port
 *
 * File Name: Port_PBcfg.h
 *
 * Description: Post Build Configuration header file for TM4C123GH6PM Microcontroller - Port Driver
 *
 * Author: Adham Muhammed
 ******************************************************************************/

#ifndef PORT_PBCFG_H_
#define PORT_PBCFG_H_

/*
 * Module Version 1.0.0
 */
#define PORT_PBCFG_SW_MAJOR_VERSION              (1U)
#define PORT_PBCFG_SW_MINOR_VERSION              (0U)
#define PORT_PBCFG_SW_PATCH_VERSION              (0U)

/*
 * AUTOSAR Version 4.0.3
 */
#define PORT_PBCFG_AR_RELEASE_MAJOR_VERSION     (4U)
#define PORT_PBCFG_AR_RELEASE_MINOR_VERSION     (0U)
#define PORT_PBCFG_AR_RELEASE_PATCH_VERSION     (3U)

/*******************************************************************************
 *                              Module Data Types                              *
 *******************************************************************************/
/* Type definition for Port_Type (Port id) used by the PORT APIs */
typedef uint8 Port_Type;

/* Type definition for Port_PinType (channel id) used by the PORT APIs */
typedef uint8 Port_PinType;

/* Type definition for Port_PinModeType (channel mode) used by the PORT APIs */
typedef enum
{
    PORT_PIN_MODE_DIO         , PORT_PIN_MODE_ALTERNATE_1 , PORT_PIN_MODE_ALTERNATE_2 , PORT_PIN_MODE_ALTERNATE_3 ,
    PORT_PIN_MODE_ALTERNATE_4 , PORT_PIN_MODE_ALTERNATE_5 , PORT_PIN_MODE_ALTERNATE_6 , PORT_PIN_MODE_ALTERNATE_7,
    PORT_PIN_MODE_ALTERNATE_8 , PORT_PIN_MODE_ALTERNATE_9 , PORT_PIN_MODE_ALTERNATE_14=14 , PORT_PIN_MODE_ANALOG
}Port_PinModeType;

/* Enum for Port_PinDirectionType */
typedef enum
{
    PORT_PIN_IN,PORT_PIN_OUT
}Port_PinDirectionType;

/* Enum to hold internal resistor type for PIN */
typedef enum
{
    PORT_PIN_INTERNAL_RESISTOR_OFF,PORT_PIN_INTERNAL_RESISTOR_PULL_UP,PORT_PIN_INTERNAL_RESISTOR_PULL_DOWN
}Port_InternalResistor;

/* Enum for Port_PinLevelValue */
typedef enum
{
    PORT_PIN_LEVEL_LOW,PORT_PIN_LEVEL_HIGH
}Port_PinLevelValue;

/* Type of the external data structure containing the initialization data for Port module. */
typedef struct
{
    Port_Type             port_id;
    Port_PinType          pin_id;
    Port_PinDirectionType pin_direction;
    Port_PinModeType      pin_mode;
    Port_InternalResistor port_internalResistor;
    Port_PinLevelValue    pin_levelValue;
    boolean               port_pinModeChangeable;
    boolean               port_pinDirectionChangeable;
}Pin_ConfigType;

/* Data Structure required for initializing All the ports pin's configurations*/
typedef struct
{
    Pin_ConfigType pins_config [PORT_CONFIGURED_CHANNLES];
}Port_ConfigType;

/*******************************************************************************
 *                       External Variables                                    *
 *******************************************************************************/

/* Extern PB structures to be used by Port and other modules */
extern const Port_ConfigType Port_Configuration;



#endif /* PORT_PBCFG_H_ */
