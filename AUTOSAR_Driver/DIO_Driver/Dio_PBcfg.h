 /******************************************************************************
 *
 * Module: Dio
 *
 * File Name: Dio_PBcfg.h
 *
 * Description: Post Build Configuration header file for TM4C123GH6PM Microcontroller - Dio Driver
 *
 * Author: Ahmed AbdElgleel
 ******************************************************************************/
#ifndef DIO_PBCFG_H_
#define DIO_PBCFG_H_

/*
 * Module Version 1.0.0
 */
#define DIO_PBCFG_SW_MAJOR_VERSION                (1U)
#define DIO_PBCFG_SW_MINOR_VERSION                (0U)
#define DIO_PBCFG_SW_PATCH_VERSION                (0U)

/*
 * AUTOSAR Version 4.0.3
 */
#define DIO_PBCFG_AR_RELEASE_MAJOR_VERSION        (4U)
#define DIO_PBCFG_AR_RELEASE_MINOR_VERSION        (0U)
#define DIO_PBCFG_AR_RELEASE_PATCH_VERSION        (3U)

/*******************************************************************************
 *                              Module Data Types                              *
 *******************************************************************************/

/* types and function found in chapter 8 api specifications */

/* Type definition for Dio_ChannelType used by the DIO APIs */
typedef uint8 Dio_ChannelType;

/* Type definition for Dio_PortType used by the DIO APIs */
typedef uint8 Dio_PortType;

/* Type definition for Dio_LevelType used by the DIO APIs */
typedef uint8 Dio_LevelType;

/* Type definition for Dio_PortLevelType used by the DIO APIs */
typedef uint8 Dio_PortLevelType;

typedef struct
{
    /* Member contains the ID of the Port that this channel belongs to */
    Dio_PortType Port_Num;
    /* Member contains the ID of the Channel*/
    Dio_ChannelType Ch_Num;
}Dio_ConfigChannel;

/* Data Structure required for initializing the Dio Driver */

/* Structure for Dio_ChannelGroup */
typedef struct
{
  /* Mask which defines the positions of the channel group */
  uint8 mask;
  /* Position of the group from LSB */
  uint8 offset;
  /* This shall be the port ID which the Channel group is defined. */
  Dio_PortType PortIndex;
} Dio_ChannelGroupType;

typedef struct Dio_ConfigType
{
    Dio_ConfigChannel Channels[DIO_CONFIGURED_CHANNLES];
    Dio_PortType Ports[DIO_CONFIGURED_PORTS];
    Dio_ChannelGroupType Groups[DIO_CONFIGURED_GROUPS];
} Dio_ConfigType;

/*******************************************************************************
 *                       External Variables                                    *
 *******************************************************************************/

/* Extern PB structures to be used by Dio and other modules */
extern const Dio_ConfigType Dio_Configuration;


#endif /* DIO_PBCFG_H_ */
