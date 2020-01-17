#include <xCore.h>
#include <xRL0x.h>
#include "Almanac.h"

#define RL03_FREQ 915.0


void setup() 
{
    Serial.begin(115200);
    Wire.begin();
    Serial.print("Size: ");
    Serial.println(sizeof(almanac));

     if (!RL0X.begin()) { // <-- enter radio name here
    Serial.println("Check the connector to CR01");
    while (1) {
      // Flash RED to indicate failure
      delay(100);
    }
  } else {
    // RL0X Initialized correctly
    //RL0X.setModemConfig(RL01.Bw31_25Cr48Sf512);
    RL0X.setFrequency(RL03_FREQ);
    RL0X.setTxPower(23, false);
  }

}

void loop()
{
    Serial.println("Sending to RL0X Server");

    for(int i = 0; i < 124; i+=10)
    {
        uint8_t packet [10] {0};
        std::copy(almanac + i, almanac + i + 10, packet + 0);

        Serial.write(packet,sizeof(packet));

        delay(100);
        RL0X.send(packet, sizeof(packet));
        
    }

    

    uint8_t buf[195];
    uint8_t len = sizeof(buf);

    if (RL0X.waitAvailableTimeout(3000)) 
    {
        if (RL0X.recv(buf, &len)) 
        {
            Serial.print("got reply: ");
            Serial.println((char*)buf);
            Serial.print("RSSI: ");
            Serial.println(RL0X.lastRssi(), DEC);
        } 
        else 
        {
            Serial.println("recv failed");
        }
    } 
    else 
    {
        Serial.println("No reply, is the RL01 server running ?");
    }
}
