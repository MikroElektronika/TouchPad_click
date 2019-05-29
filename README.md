![MikroE](http://www.mikroe.com/img/designs/beta/logo_small.png)

---

# Touchpad Click

- **CIC Prefix**  : TOUCHPAD
- **Author**      : MikroE Team
- **Verison**     : 1.0.0
- **Date**        : Jul 2018.

---


### Software Support

We provide a library for the Touchpad Click on our [LibStock](https://libstock.mikroe.com/projects/view/1634/touchpad-click) 
page, as well as a demo application (example), developed using MikroElektronika 
[compilers](http://shop.mikroe.com/compilers). The demo can run on all the main 
MikroElektronika [development boards](http://shop.mikroe.com/development-boards).

**Library Description**

The library contains all the functions required to operate the Touchpad click.

Key functions :

- ``` void touchpad_getPosition( T_touchpad_touchPoint *posData ) ``` - Gets coordinate X and Y of touch and puts them in structure touch_point
- ``` void touchpad_readRegister( uint8_t rAddr, uint8_t *buffer) ``` - Reads register on rAddr address and returns value through buffer 
- ``` void touchpad_writeGesture( uint8_t _data, char *str ) ``` - Writes gesture through *str based on red value _data 
- ``` void touchpad_readBytes( uint8_t rAddr, uint8_t *buffer, uint8_t nBytes) ``` - Reads register for more bytes on consecutive addresses and returns value through buffer

**Examples Description**

The application is composed of three sections :

- System Initialization - Initializes I2C module and sets INT pin as OUTPUT and RST pin as INPUT.
- Application Initialization - Initializes driver init. 
- Application Task - (code snippet) - Reads every touch and gesture and logs to USBUART_A.

```.c
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
```

The full application code, and ready to use projects can be found on our 
[LibStock](https://libstock.mikroe.com/projects/view/1634/touchpad-click) page.

Other mikroE Libraries used in the example:

- I2C

**Additional notes and informations**

Depending on the development board you are using, you may need 
[USB UART click](http://shop.mikroe.com/usb-uart-click), 
[USB UART 2 Click](http://shop.mikroe.com/usb-uart-2-click) or 
[RS232 Click](http://shop.mikroe.com/rs232-click) to connect to your PC, for 
development systems with no UART to USB interface available on the board. The 
terminal available in all Mikroelektronika 
[compilers](http://shop.mikroe.com/compilers), or any other terminal application 
of your choice, can be used to read the message.

---
---
