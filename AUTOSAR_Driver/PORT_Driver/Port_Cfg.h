/******************************************************************************
 *
 * Module: Port
 *
 * File Name: Port_Cfg.h
 *
 * Description: Pre-Compile Configuration Header file for TM4C123GH6PM Microcontroller - Port Driver
 *
 * Author: Adham Muhammed
 ******************************************************************************/

#ifndef PORT_CFG_H_
#define PORT_CFG_H_

/*
 * Module Version 1.0.0
 */
#define PORT_CFG_SW_MAJOR_VERSION              (1U)
#define PORT_CFG_SW_MINOR_VERSION              (0U)
#define PORT_CFG_SW_PATCH_VERSION              (0U)

/*
 * AUTOSAR Version 4.0.3
 */
#define PORT_CFG_AR_RELEASE_MAJOR_VERSION     (4U)
#define PORT_CFG_AR_RELEASE_MINOR_VERSION     (0U)
#define PORT_CFG_AR_RELEASE_PATCH_VERSION     (3U)

/* Pre-compile option for Development Error Detect */
#define PORT_DEV_ERROR_DETECT                (STD_ON)

/* Pre-compile option for Adds / removes the service Port_SetPinDirection() */
#define PORT_SET_PIN_DIRECTION_API           (STD_OFF)

/* Pre-compile option for Adds / removes the service Port_SetPinMode() */
#define PORT_SET_PIN_MODE_API                (STD_OFF)

/* Pre-compile option for Adds / removes the service Gpt_GetVersionInfo() */
#define PORT_VERSION_INFO_API                (STD_OFF)

/* Number of the configured Port Channels Excluded JTAG PINS */
#define PORT_CONFIGURED_CHANNLES             (39U)

/* Channel Index in the array of structures in Port_PBcfg.c */
#define PortConf_CHANNEL_A0_ID_INDEX         (uint8)0x00        /*index 0*/
#define PortConf_CHANNEL_A1_ID_INDEX         (uint8)0x01        /*index 1*/
#define PortConf_CHANNEL_A2_ID_INDEX         (uint8)0x02        /*index 2*/
#define PortConf_CHANNEL_A3_ID_INDEX         (uint8)0x03        /*index 3*/
#define PortConf_CHANNEL_A4_ID_INDEX         (uint8)0x04        /*index 4*/
#define PortConf_CHANNEL_A5_ID_INDEX         (uint8)0x06        /*index 5*/
#define PortConf_CHANNEL_A6_ID_INDEX         (uint8)0x05        /*index 6*/
#define PortConf_CHANNEL_A7_ID_INDEX         (uint8)0x07        /*index 7*/

#define PortConf_CHANNEL_B0_ID_INDEX         (uint8)0x08        /*index 8*/
#define PortConf_CHANNEL_B1_ID_INDEX         (uint8)0x09        /*index 9*/
#define PortConf_CHANNEL_B2_ID_INDEX         (uint8)0x0A        /*index 10*/
#define PortConf_CHANNEL_B3_ID_INDEX         (uint8)0x0B        /*index 11*/
#define PortConf_CHANNEL_B4_ID_INDEX         (uint8)0x0C        /*index 12*/
#define PortConf_CHANNEL_B5_ID_INDEX         (uint8)0x0D        /*index 13*/
#define PortConf_CHANNEL_B6_ID_INDEX         (uint8)0x0E        /*index 14*/
#define PortConf_CHANNEL_B7_ID_INDEX         (uint8)0x0F        /*index 15*/

#define PortConf_CHANNEL_C4_ID_INDEX         (uint8)0x10        /*index 16*/
#define PortConf_CHANNEL_C5_ID_INDEX         (uint8)0x11        /*index 17*/
#define PortConf_CHANNEL_C6_ID_INDEX         (uint8)0x12        /*index 18*/
#define PortConf_CHANNEL_C7_ID_INDEX         (uint8)0x13        /*index 19*/


#define PortConf_CHANNEL_D0_ID_INDEX         (uint8)0x14        /*index 20*/
#define PortConf_CHANNEL_D1_ID_INDEX         (uint8)0x15        /*index 21*/
#define PortConf_CHANNEL_D2_ID_INDEX         (uint8)0x16        /*index 22*/
#define PortConf_CHANNEL_D3_ID_INDEX         (uint8)0x17        /*index 23*/
#define PortConf_CHANNEL_D4_ID_INDEX         (uint8)0x18        /*index 24*/
#define PortConf_CHANNEL_D5_ID_INDEX         (uint8)0x19        /*index 25*/
#define PortConf_CHANNEL_D6_ID_INDEX         (uint8)0x1A        /*index 26*/
#define PortConf_CHANNEL_D7_ID_INDEX         (uint8)0x1B        /*index 27*/

#define PortConf_CHANNEL_E0_ID_INDEX         (uint8)0x1C        /*index 28*/
#define PortConf_CHANNEL_E1_ID_INDEX         (uint8)0x1D        /*index 29*/
#define PortConf_CHANNEL_E2_ID_INDEX         (uint8)0x1E        /*index 30*/
#define PortConf_CHANNEL_E3_ID_INDEX         (uint8)0x1F        /*index 31*/
#define PortConf_CHANNEL_E4_ID_INDEX         (uint8)0x20        /*index 32*/
#define PortConf_CHANNEL_E5_ID_INDEX         (uint8)0x21        /*index 33*/

#define PortConf_CHANNEL_F0_ID_INDEX         (uint8)0x22        /*index 34*/
#define PortConf_CHANNEL_F1_ID_INDEX         (uint8)0x23        /*index 35*/
#define PortConf_CHANNEL_F2_ID_INDEX         (uint8)0x24        /*index 36*/
#define PortConf_CHANNEL_F3_ID_INDEX         (uint8)0x25        /*index 37*/
#define PortConf_CHANNEL_F4_ID_INDEX         (uint8)0x26        /*index 38*/

#endif /* PORT_CFG_H_ */
