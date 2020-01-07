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
#include "X_VALUES.h"

xOD01 OD01;

//Set up 
void setup()
{
  Wire.begin();
  OD01.begin();
  ssd1306_128x64_i2c_init();

  
}

void loop()
{
  display_logo(3000);
  display_title_screen(3000);
  display_connect_wifi();
  display_starting_screen(3000);
  dislay_connecting_FS();
  display_connected_screen();
  delay(2000);
}
