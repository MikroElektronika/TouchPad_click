/*
    __touchpad_driver.c

-----------------------------------------------------------------------------

  This file is part of mikroSDK.

  Copyright (c) 2017, MikroElektonika - http://www.mikroe.com

  All rights reserved.

----------------------------------------------------------------------------- */

#include "__touchpad_driver.h"
#include "__touchpad_hal.c"

/* ------------------------------------------------------------------- MACROS */

const uint8_t _TOUCHPAD_MTCH6102_I2C                 =  0x25;  /**< Slave address*/
const uint8_t _TOUCHPAD_TOUCHSTATE                   =  0x10;  /**< Touch state*/
const uint8_t _TOUCHPAD_TOUCHX                       =  0x11;  /**< Touch X*/
const uint8_t _TOUCHPAD_TOUCHY                       =  0x12;  /**< Touch Y*/
const uint8_t _TOUCHPAD_TOUCHLSB                     =  0x13;  /**< Touch XY*/
const uint8_t _TOUCHPAD_GESTURESTATE                 =  0x14;  /**< Gestrure state*/

// mode configuration bits
const uint8_t _TOUCHPAD_TOUCH_ONLY                   =  0x01;  /**< Touch only*/
const uint8_t _TOUCHPAD_GESTURE                      =  0x02;  /**< Gesture*/

// gesture state
const uint8_t _TOUCHPAD_NO_GESTURE_PRESENT           =  0x00;  /**< No Gesture Present*/
const uint8_t _TOUCHPAD_SINGLE_CLICK                 =  0x10;  /**< Single Click*/
const uint8_t _TOUCHPAD_CLICK_AND_HOLD               =  0x11;  /**< Click and Hold*/
const uint8_t _TOUCHPAD_DOUBLE_CLICK                 =  0x20;  /**< Double Click*/
const uint8_t _TOUCHPAD_DOWN_SWIPE                   =  0x31;  /**< Down Swipe*/
const uint8_t _TOUCHPAD_DOWN_SWIPE_AND_HOLD          =  0x32;  /**< Down Swipe and Hold*/
const uint8_t _TOUCHPAD_RIGHT_SWIPE                  =  0x41;  /**< Right Swipe*/
const uint8_t _TOUCHPAD_RIGHT_SWIPE_AND_HOLD         =  0x42;  /**< Right Swipe and Hold*/
const uint8_t _TOUCHPAD_UP_SWIPE                     =  0x51;  /**< Up Swipe*/
const uint8_t _TOUCHPAD_UP_SWIPE_AND_HOLD            =  0x52;  /**< Up Swipe and Hold*/
const uint8_t _TOUCHPAD_LEFT_SWIPE                   =  0x61;  /**< Left Swipe*/
const uint8_t _TOUCHPAD_LEFT_SWIPE_AND_HOLD          =  0x62;  /**< Left Swipe and Hold*/

/* ---------------------------------------------------------------- VARIABLES */

#ifdef   __TOUCHPAD_DRV_I2C__
static uint8_t _slaveAddress;
#endif

/* -------------------------------------------- PRIVATE FUNCTION DECLARATIONS */

static uint8_t *_strcpy(uint8_t *d, const uint8_t *s);

/* --------------------------------------------- PRIVATE FUNCTION DEFINITIONS */

static uint8_t *_strcpy(uint8_t *d, const uint8_t *s)
{
   uint8_t *saved = d;
   for ( ; *s; d++, s++ )
       *d = *s;
   *d = '\0';
   return saved;
}


/* --------------------------------------------------------- PUBLIC FUNCTIONS */

#ifdef   __TOUCHPAD_DRV_SPI__

void touchpad_spiDriverInit(T_TOUCHPAD_P gpioObj, T_TOUCHPAD_P spiObj)
{
    hal_spiMap( (T_HAL_P)spiObj );
    hal_gpioMap( (T_HAL_P)gpioObj );

    // ... power ON
    // ... configure CHIP
}
#endif
#ifdef   __TOUCHPAD_DRV_I2C__

void touchpad_i2cDriverInit(T_TOUCHPAD_P gpioObj, T_TOUCHPAD_P i2cObj, uint8_t slave)
{
    _slaveAddress = slave;
    hal_i2cMap( (T_HAL_P)i2cObj );
    hal_gpioMap( (T_HAL_P)gpioObj );

    // ... power ON
    // ... configure CHIP
}

#endif
#ifdef   __TOUCHPAD_DRV_UART__

void touchpad_uartDriverInit(T_TOUCHPAD_P gpioObj, T_TOUCHPAD_P uartObj)
{
    hal_uartMap( (T_HAL_P)uartObj );
    hal_gpioMap( (T_HAL_P)gpioObj );

    // ... power ON
    // ... configure CHIP
}

#endif

// GPIO Only Drivers - remove in other cases
void touchpad_gpioDriverInit(T_TOUCHPAD_P gpioObj)
{
    hal_gpioMap( (T_HAL_P)gpioObj );

    // ... power ON
}
/* ----------------------------------------------------------- IMPLEMENTATION */


void touchpad_writeGesture( uint8_t _data, char *str )
{
  switch( _data )
  {
    case _TOUCHPAD_CLICK_AND_HOLD :
                        _strcpy( str, "Click and Hold" );
                        break;
    case _TOUCHPAD_DOUBLE_CLICK :
                        _strcpy( str, "Double Click" );
                        break;
    case _TOUCHPAD_SINGLE_CLICK :
                        _strcpy( str, "Single Click" );
                        break;
    case _TOUCHPAD_DOWN_SWIPE :
                        _strcpy( str, "Down Swipe" );
                        break;
    case _TOUCHPAD_DOWN_SWIPE_AND_HOLD :
                        _strcpy( str, "Down Swipe and Hold" );
                        break;
    case _TOUCHPAD_RIGHT_SWIPE :
                        _strcpy( str, "Right Swipe" );
                        break;
    case _TOUCHPAD_RIGHT_SWIPE_AND_HOLD :
                        _strcpy( str, "Right Swipe and Hold" );
                        break;
    case _TOUCHPAD_UP_SWIPE :
                        _strcpy( str, "Up Swipe" );
                        break;
    case _TOUCHPAD_UP_SWIPE_AND_HOLD :
                        _strcpy( str, "Up Swipe and Hold" );
                        break;
    case _TOUCHPAD_LEFT_SWIPE :
                        _strcpy( str, "Left Swipe" );
                        break;
    case _TOUCHPAD_LEFT_SWIPE_AND_HOLD :
                        _strcpy( str, "Left Swipe and Hold" );
                        break;
    default :
                        break;
  }
}

void touchpad_getPosition( T_touchpad_touchPoint *posData )
{
   uint8_t tmp_data[3];

   touchpad_readBytes( _TOUCHPAD_TOUCHX, &tmp_data[0], 3 );

   posData->posX = tmp_data[0];
   posData->posX = ( posData->posX << 3 ) | ( tmp_data[2] >> 4 );
   posData->posY = tmp_data[1];
   posData->posY = ( posData->posY << 3 ) | ( tmp_data[2] & 0x0F );
}

void touchpad_readRegister( uint8_t rAddr, uint8_t *buffer)
{
   uint8_t regAddr;
   regAddr = rAddr;

   hal_i2cStart();
   hal_i2cWrite( _slaveAddress, &regAddr, 1, END_MODE_RESTART );
   hal_i2cRead( _slaveAddress, buffer, 1, END_MODE_STOP );
}

void touchpad_readBytes( uint8_t rAddr, uint8_t *buffer, uint8_t nBytes)
{
   uint8_t regAddr;
   regAddr = rAddr;

   hal_i2cStart();
   hal_i2cWrite( _slaveAddress, &regAddr, 1, END_MODE_RESTART );
   hal_i2cRead( _slaveAddress, buffer, nBytes, END_MODE_STOP );
}

/* -------------------------------------------------------------------------- */
/*
  __touchpad_driver.c

  Copyright (c) 2017, MikroElektonika - http://www.mikroe.com

  All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright
   notice, this list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright
   notice, this list of conditions and the following disclaimer in the
   documentation and/or other materials provided with the distribution.

3. All advertising materials mentioning features or use of this software
   must display the following acknowledgement:
   This product includes software developed by the MikroElektonika.

4. Neither the name of the MikroElektonika nor the
   names of its contributors may be used to endorse or promote products
   derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY MIKROELEKTRONIKA ''AS IS'' AND ANY
EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL MIKROELEKTRONIKA BE LIABLE FOR ANY
DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

----------------------------------------------------------------------------- */