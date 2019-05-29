/*
    __touchpad_driver.h

-----------------------------------------------------------------------------

  This file is part of mikroSDK.
  
  Copyright (c) 2017, MikroElektonika - http://www.mikroe.com

  All rights reserved.

----------------------------------------------------------------------------- */

/**
@file   __touchpad_driver.h
@brief    Touchpad Driver
@mainpage Touchpad Click
@{

@image html libstock_fb_view.jpg

@}

@defgroup   TOUCHPAD
@brief      Touchpad Click Driver
@{

| Global Library Prefix | **TOUCHPAD** |
|:---------------------:|:-----------------:|
| Version               | **1.0.0**    |
| Date                  | **Jul 2018.**      |
| Developer             | **MikroE Team**     |

*/
/* -------------------------------------------------------------------------- */

#include "stdint.h"

#ifndef _TOUCHPAD_H_
#define _TOUCHPAD_H_

/** 
 * @macro T_TOUCHPAD_P
 * @brief Driver Abstract type 
 */
#define T_TOUCHPAD_P    const uint8_t*

/** @defgroup TOUCHPAD_COMPILE Compilation Config */              /** @{ */

//  #define   __TOUCHPAD_DRV_SPI__                            /**<     @macro __TOUCHPAD_DRV_SPI__  @brief SPI driver selector */
   #define   __TOUCHPAD_DRV_I2C__                            /**<     @macro __TOUCHPAD_DRV_I2C__  @brief I2C driver selector */                                          
// #define   __TOUCHPAD_DRV_UART__                           /**<     @macro __TOUCHPAD_DRV_UART__ @brief UART driver selector */ 

                                                                       /** @} */
/** @defgroup TOUCHPAD_VAR Variables */                           /** @{ */


extern const uint8_t _TOUCHPAD_MTCH6102_I2C;                /**< Slave address*/

extern const uint8_t _TOUCHPAD_TOUCHSTATE;                  /**< Touch state*/
extern const uint8_t _TOUCHPAD_TOUCHX;                     /**< Touch X*/
extern const uint8_t _TOUCHPAD_TOUCHY;                      /**< Touch Y*/
extern const uint8_t _TOUCHPAD_TOUCHLSB;                    /**< Touch XY*/
extern const uint8_t _TOUCHPAD_GESTURESTATE;                /**< Gestrure state*/

// mode configuration bits
extern const uint8_t _TOUCHPAD_TOUCH_ONLY;                  /**< Touch only*/
extern const uint8_t _TOUCHPAD_GESTURE;                     /**< Gesture*/

// gesture state
extern const uint8_t _TOUCHPAD_NO_GESTURE_PRESENT;          /**< No Gesture Present*/
extern const uint8_t _TOUCHPAD_SINGLE_CLICK;                /**< Single Click*/
extern const uint8_t _TOUCHPAD_CLICK_AND_HOLD;              /**< Click and Hold*/
extern const uint8_t _TOUCHPAD_DOUBLE_CLICK;                /**< Double Click*/
extern const uint8_t _TOUCHPAD_DOWN_SWIPE;                  /**< Down Swipe*/
extern const uint8_t _TOUCHPAD_DOWN_SWIPE_AND_HOLD;         /**< Down Swipe and Hold*/
extern const uint8_t _TOUCHPAD_RIGHT_SWIPE;                 /**< Right Swipe*/
extern const uint8_t _TOUCHPAD_RIGHT_SWIPE_AND_HOLD;        /**< Right Swipe and Hold*/
extern const uint8_t _TOUCHPAD_UP_SWIPE;                    /**< Up Swipe*/
extern const uint8_t _TOUCHPAD_UP_SWIPE_AND_HOLD;           /**< Up Swipe and Hold*/
extern const uint8_t _TOUCHPAD_LEFT_SWIPE;                  /**< Left Swipe*/
extern const uint8_t _TOUCHPAD_LEFT_SWIPE_AND_HOLD;         /**< Left Swipe and Hold*/

                                                                       /** @} */
/** @defgroup TOUCHPAD_TYPES Types */                             /** @{ */

typedef struct
{
     uint16_t posX;  /**< X position*/
     uint8_t posY;  /**< Y position*/

} T_touchpad_touchPoint;


                                                                       /** @} */
#ifdef __cplusplus
extern "C"{
#endif

/** @defgroup TOUCHPAD_INIT Driver Initialization */              /** @{ */

#ifdef   __TOUCHPAD_DRV_SPI__
void touchpad_spiDriverInit(T_TOUCHPAD_P gpioObj, T_TOUCHPAD_P spiObj);
#endif
#ifdef   __TOUCHPAD_DRV_I2C__
void touchpad_i2cDriverInit(T_TOUCHPAD_P gpioObj, T_TOUCHPAD_P i2cObj, uint8_t slave);
#endif
#ifdef   __TOUCHPAD_DRV_UART__
void touchpad_uartDriverInit(T_TOUCHPAD_P gpioObj, T_TOUCHPAD_P uartObj);
#endif

// GPIO Only Drivers - remove in other cases
void touchpad_gpioDriverInit(T_TOUCHPAD_P gpioObj);
                                                                       /** @} */
/** @defgroup TOUCHPAD_FUNC Driver Functions */                   /** @{ */

/** Gets coordinate X and Y of touch and puts them in structure touch_point */
void touchpad_getPosition( T_touchpad_touchPoint *posData );

/** Reads register on rAddr address and returns value through buffer */
void touchpad_readRegister( uint8_t rAddr, uint8_t *buffer);

/** Writes gesture through *str based on red value _data */
void touchpad_writeGesture( uint8_t _data, char *str );

/** Reads register for more bytes on consecutive addresses and returns value through buffer */
void touchpad_readBytes( uint8_t rAddr, uint8_t *buffer, uint8_t nBytes);

                                                                       /** @} */
#ifdef __cplusplus
} // extern "C"
#endif
#endif

/**
    @example Click_Touchpad_STM.c
    @example Click_Touchpad_TIVA.c
    @example Click_Touchpad_CEC.c
    @example Click_Touchpad_KINETIS.c
    @example Click_Touchpad_MSP.c
    @example Click_Touchpad_PIC.c
    @example Click_Touchpad_PIC32.c
    @example Click_Touchpad_DSPIC.c
    @example Click_Touchpad_AVR.c
    @example Click_Touchpad_FT90x.c
    @example Click_Touchpad_STM.mbas
    @example Click_Touchpad_TIVA.mbas
    @example Click_Touchpad_CEC.mbas
    @example Click_Touchpad_KINETIS.mbas
    @example Click_Touchpad_MSP.mbas
    @example Click_Touchpad_PIC.mbas
    @example Click_Touchpad_PIC32.mbas
    @example Click_Touchpad_DSPIC.mbas
    @example Click_Touchpad_AVR.mbas
    @example Click_Touchpad_FT90x.mbas
    @example Click_Touchpad_STM.mpas
    @example Click_Touchpad_TIVA.mpas
    @example Click_Touchpad_CEC.mpas
    @example Click_Touchpad_KINETIS.mpas
    @example Click_Touchpad_MSP.mpas
    @example Click_Touchpad_PIC.mpas
    @example Click_Touchpad_PIC32.mpas
    @example Click_Touchpad_DSPIC.mpas
    @example Click_Touchpad_AVR.mpas
    @example Click_Touchpad_FT90x.mpas
*/                                                                     /** @} */
/* -------------------------------------------------------------------------- */
/*
  __touchpad_driver.h

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