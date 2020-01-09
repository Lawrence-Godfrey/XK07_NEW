#include <xCore.h>
#include <xRL0x.h>

#define RL03_FREQ 915.0

void setup()
{
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_RED, OUTPUT);
  Serial.begin(115200);
  Wire.begin();

   if (!RL0X.begin()) { // <-- enter radio name here
    Serial.println("Check the connector to CR01");
    while (1) {
      // Flash RED to indicate failure
      digitalWrite(CW01_RED, HIGH);
      delay(100);
      digitalWrite(CW01_RED, LOW);
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

    digitalWrite(CW01_GREEN, HIGH);

    uint8_t data[] = "Hello World!";
    delay(100);
    RL0X.send(data, sizeof(data));

    uint8_t buf[195];
    uint8_t len = sizeof(buf);

    if (RL0X.waitAvailableTimeout(3000)) {
        if (RL0X.recv(buf, &len)) {
            Serial.print("got reply: ");
            Serial.println((char*)buf);
            Serial.print("RSSI: ");
            Serial.println(RL0X.lastRssi(), DEC);
        } else {
            Serial.println("recv failed");
        }
    } else {
        digitalWrite(CW01_GREEN, LOW);
        Serial.println("No reply, is the RL01 server running ?");
    }
}