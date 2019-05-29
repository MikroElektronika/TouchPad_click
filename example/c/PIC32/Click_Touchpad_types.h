#ifndef _TOUCHPAD_T_
#define _TOUCHPAD_T_

#include "stdint.h"

#ifndef _TOUCHPAD_H_

#define T_TOUCHPAD_P const uint8_t* 

typedef struct
{
     uint16_t posX;
     uint8_t posY;

} T_touchpad_touchPoint;

#endif
#endif