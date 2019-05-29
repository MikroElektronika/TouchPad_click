#line 1 "D:/Clicks_git/T/TouchPad_Click/SW/example/c/ARM/STM/Click_Touchpad_STM.c"
#line 1 "d:/clicks_git/t/touchpad_click/sw/example/c/arm/stm/click_touchpad_types.h"
#line 1 "c:/users/public/documents/mikroelektronika/mikroc pro for arm/include/stdint.h"





typedef signed char int8_t;
typedef signed int int16_t;
typedef signed long int int32_t;
typedef signed long long int64_t;


typedef unsigned char uint8_t;
typedef unsigned int uint16_t;
typedef unsigned long int uint32_t;
typedef unsigned long long uint64_t;


typedef signed char int_least8_t;
typedef signed int int_least16_t;
typedef signed long int int_least32_t;
typedef signed long long int_least64_t;


typedef unsigned char uint_least8_t;
typedef unsigned int uint_least16_t;
typedef unsigned long int uint_least32_t;
typedef unsigned long long uint_least64_t;



typedef signed long int int_fast8_t;
typedef signed long int int_fast16_t;
typedef signed long int int_fast32_t;
typedef signed long long int_fast64_t;


typedef unsigned long int uint_fast8_t;
typedef unsigned long int uint_fast16_t;
typedef unsigned long int uint_fast32_t;
typedef unsigned long long uint_fast64_t;


typedef signed long int intptr_t;
typedef unsigned long int uintptr_t;


typedef signed long long intmax_t;
typedef unsigned long long uintmax_t;
#line 10 "d:/clicks_git/t/touchpad_click/sw/example/c/arm/stm/click_touchpad_types.h"
typedef struct
{
 uint16_t posX;
 uint8_t posY;

} T_touchpad_touchPoint;
#line 1 "d:/clicks_git/t/touchpad_click/sw/example/c/arm/stm/click_touchpad_config.h"
#line 1 "d:/clicks_git/t/touchpad_click/sw/example/c/arm/stm/click_touchpad_types.h"
#line 3 "d:/clicks_git/t/touchpad_click/sw/example/c/arm/stm/click_touchpad_config.h"
const uint32_t _TOUCHPAD_I2C_CFG[ 1 ] =
{
 100000
};
#line 28 "D:/Clicks_git/T/TouchPad_Click/SW/example/c/ARM/STM/Click_Touchpad_STM.c"
char touchpad_text[40];
uint8_t touchpad_data;
T_touchpad_touchPoint touchpad_posData;

void systemInit()
{
 mikrobus_gpioInit( _MIKROBUS1, _MIKROBUS_INT_PIN, _GPIO_OUTPUT );
 mikrobus_gpioInit( _MIKROBUS1, _MIKROBUS_RST_PIN, _GPIO_INPUT );


 mikrobus_i2cInit( _MIKROBUS1, &_TOUCHPAD_I2C_CFG[0] );


 mikrobus_logInit( _LOG_USBUART_A , 9600 );

 Delay_ms( 100 );
}

void applicationInit()
{
 touchpad_i2cDriverInit( ( const uint8_t* )&_MIKROBUS1_GPIO, ( const uint8_t* )&_MIKROBUS1_I2C, _TOUCHPAD_MTCH6102_I2C );
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
