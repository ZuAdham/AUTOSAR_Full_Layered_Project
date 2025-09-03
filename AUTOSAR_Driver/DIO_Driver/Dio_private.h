 /******************************************************************************
 *
 * Module: Dio
 *
 * File Name: Dio_Private.h
 *
 * Description: Header file for TM4C123GH6PM Microcontroller - Dio Driver Registers and Private Macros
 *
 * Author: Adham Muhammed
 ******************************************************************************/

#ifndef DIO_PRIVATE_H
#define DIO_PRIVATE_H

#include "Dio.h"
#include "Common_Macros.h"

/*
 * Macros for Dio Status
 */
#define DIO_INITIALIZED                (1U)
#define DIO_NOT_INITIALIZED            (0U)

/*******************************************************************
 *             DIO Registers type structure declaration           *
 *******************************************************************/
typedef union
{
    uint8 Byte;
    struct
    {
        uint8 DATA_0:1;
        uint8 DATA_1:1;
        uint8 DATA_2:1;
        uint8 DATA_3:1;
        uint8 DATA_4:1;
        uint8 DATA_5:1;
        uint8 DATA_6:1;
        uint8 DATA_7:1;
    }Bits;
} GPIO_PORTA_DATA_REG_TYPE;

typedef union
{
    uint8 Byte;
    struct
    {
        uint8 DATA_0:1;
        uint8 DATA_1:1;
        uint8 DATA_2:1;
        uint8 DATA_3:1;
        uint8 DATA_4:1;
        uint8 DATA_5:1;
        uint8 DATA_6:1;
        uint8 DATA_7:1;
    }Bits;
} GPIO_PORTB_DATA_REG_TYPE;

typedef union
{
    uint8 Byte;
    struct
    {
        uint8 DATA_0:1;
        uint8 DATA_1:1;
        uint8 DATA_2:1;
        uint8 DATA_3:1;
        uint8 DATA_4:1;
        uint8 DATA_5:1;
        uint8 DATA_6:1;
        uint8 DATA_7:1;
    }Bits;
} GPIO_PORTC_DATA_REG_TYPE;

typedef union
{
    uint8 Byte;
    struct
    {
        uint8 DATA_0:1;
        uint8 DATA_1:1;
        uint8 DATA_2:1;
        uint8 DATA_3:1;
        uint8 DATA_4:1;
        uint8 DATA_5:1;
        uint8 DATA_6:1;
        uint8 DATA_7:1;
    }Bits;
} GPIO_PORTD_DATA_REG_TYPE;


typedef union
{
    uint8 Byte;
    struct
    {
        uint8 DATA_0:1;
        uint8 DATA_1:1;
        uint8 DATA_2:1;
        uint8 DATA_3:1;
        uint8 DATA_4:1;
        uint8 DATA_5:1;
        uint8       :1 ;         /*padding*/
        uint8       :1 ;         /*padding*/
    }Bits;
} GPIO_PORTE_DATA_REG_TYPE;

typedef union
{
    uint8 Byte;
    struct
    {
        uint8 DATA_0:1;
        uint8 DATA_1:1;
        uint8 DATA_2:1;
        uint8 DATA_3:1;
        uint8 DATA_4:1;
        uint8       :1 ;     /*padbding*/
        uint8       :1 ;     /*padding*/
        uint8       :1 ;     /*padding*/
    }Bits;
} GPIO_PORTF_DATA_REG_TYPE;

/*******************************************************************
 *             DIO Registers type structure declaration           *
 *******************************************************************/

#define GPIO_PORTA_DATA_REG       (*((volatile GPIO_PORTA_DATA_REG_TYPE *)0x400043FC))
#define GPIO_PORTB_DATA_REG       (*((volatile GPIO_PORTB_DATA_REG_TYPE *)0x400053FC))
#define GPIO_PORTC_DATA_REG       (*((volatile GPIO_PORTC_DATA_REG_TYPE *)0x400063FC))
#define GPIO_PORTD_DATA_REG       (*((volatile GPIO_PORTD_DATA_REG_TYPE *)0x400073FC))
#define GPIO_PORTE_DATA_REG       (*((volatile GPIO_PORTE_DATA_REG_TYPE *)0x400243FC))
#define GPIO_PORTF_DATA_REG       (*((volatile GPIO_PORTF_DATA_REG_TYPE *)0x400253FC))

#endif /* DIO_PRIVATE_H */
