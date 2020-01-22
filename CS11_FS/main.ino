#include <arduino-CS11_SDU.h>
#inculde <xODO1.h>

xOD01 OD01;

void setup() {
  SerialUSB.begin(115200);
  Wire.begin();
  OD01.begin();
  OD01.clear();

  
  if (!SD.begin(3))
  {
      OD01.println("SD BEGIN");
  }
  else
  {
      OD01.println("SD BEGIN FAIL")
  }
  
  delay(5000); // wait a bit

  message += "Sketch compile date and time: ";
  message += __DATE__;
  message += " ";
  message += __TIME__;

  // print out the sketch compile date and time on the serial port
  SerialUSB.println(message);
}

void loop() {
  // add you own code here
}