/*
Example for Touchpad Click

    Date          : Jul 2018.
    Author        : MikroE Team

Test configuration FT90x :
    
    MCU                : FT900
    Dev. Board         : EasyFT90x v7 
    FT90x Compiler ver : vCANT_FIND_VERSION

---

Description :

The application is composed of three sections :

- System Initialization - Initializes I2C module and sets INT pin as OUTPUT and RST pin as INPUT.
- Application Initialization - Initializes driver init.
- Application Task - (code snippet) - Reads every touch and gesture and logs to MIKROBUS2.

*/

#include "Click_Touchpad_types.h"
#include "Click_Touchpad_config.h"

char touchpad_text[40];
uint8_t touchpad_data;
T_touchpad_touchPoint touchpad_posData;

void systemInit()
{
     mikrobus_gpioInit( _MIKROBUS1, _MIKROBUS_INT_PIN, _GPIO_OUTPUT );
     mikrobus_gpioInit( _MIKROBUS1, _MIKROBUS_RST_PIN, _GPIO_INPUT );


     mikrobus_i2cInit( _MIKROBUS1, &_TOUCHPAD_I2C_CFG[0] );


     mikrobus_logInit( _MIKROBUS2 , 9600 );

     Delay_ms( 100 );
}

void applicationInit()
{

     touchpad_i2cDriverInit( (T_TOUCHPAD_P)&_MIKROBUS1_GPIO, (T_TOUCHPAD_P)&_MIKROBUS1_I2C, _TOUCHPAD_MTCH6102_I2C );

}

void applicationInit()
{
     touchpad_i2cDriverInit( (T_TOUCHPAD_P)&_MIKROBUS1_GPIO, (T_TOUCHPAD_P)&_MIKROBUS1_I2C, _TOUCHPAD_MTCH6102_I2C );
     Delay_ms( 300 );
}

void applicationTask()
{
     Delay_ms( 50 );
     touchpad_readRegister( _TOUCHPAD_TOUCHSTATE, &touchpad_data );
     if( (touchpad_data & _TOUCHPAD_TOUCH_ONLY) != 0 )
     {
        mikrobus_logWrite( "", _LOG_LINE );
        touchpad_getPosition( &touchpad_posData );
        WordToStr( touchpad_posData.posX, touchpad_text );
        mikrobus_logWrite( "Position X: ", _LOG_TEXT );
        mikrobus_logWrite( touchpad_text, _LOG_LINE );
        WordToStr( touchpad_posData.posY, touchpad_text );
        mikrobus_logWrite( "Position Y: ", _LOG_TEXT );
        mikrobus_logWrite( touchpad_text, _LOG_LINE );
        mikrobus_logWrite( "-----------", _LOG_LINE );
        Delay_ms( 50 );
     }
     else if( (touchpad_data & _TOUCHPAD_GESTURE) != 0 )
     {
        Delay_ms( 50 );
        touchpad_readRegister( _TOUCHPAD_GESTURESTATE, &touchpad_data );
        if( touchpad_data != _TOUCHPAD_NO_GESTURE_PRESENT )
        {
           touchpad_writeGesture( touchpad_data, &touchpad_text );
           mikrobus_logWrite( touchpad_text , _LOG_LINE );
        }
     }
}

void main()
{
    systemInit();
    applicationInit();

    while (1)
    {
            applicationTask();
    }
}