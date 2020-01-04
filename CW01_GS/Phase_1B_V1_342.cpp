/*
Author: Lawrence Godfrey
Date: 3/1/2020
For use with CW01, OD01, RL0x
*/

// Arduino Libraries
#include "ssd1306.h"     // https://github.com/lexus2k/ssd1306

// Xinabox Libraries
#include <xOD01.h>

// Other
#include "X_LOGO.h"      

//Set up 
xOD01 OD01;

#ifdef ESP8266
 Wire.pins(2, 14);
#endif
 Wire.begin();

ssd1306_128x64_i2c_init();
