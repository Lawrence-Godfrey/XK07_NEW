#include <xCore.h>
#include <xRL0x.h>
#include <xCS11_SDU.h>
#include <SD.h>
#define RL03_FREQ 915.0

#define CW01_RED 11
#define CW01_GREEN 12
#define CW01_BLUE 4
  
// Radio Address
#define ADDR_ID 0x11
#define FROM_ID 0x11
#define TO_ID   0x31

File myFile;
String datafile;

void setup() {
  // Start the SerialUSB Monitor
  SerialUSB.begin(115200);
  delay(5000);
  // Set the RGB Pin directions
  pinMode(CW01_RED, OUTPUT);
  pinMode(CW01_GREEN, OUTPUT);
  pinMode(CW01_BLUE, OUTPUT);

  // Start the I2C Comunication
 
  Wire.begin();

  if (SD.begin(3))
  {
    SerialUSB.println("SD card initialized");
  }

   datafile = "assist.ubx";
  


  if (!RL0X.begin()) { // <-- enter radio name here
    SerialUSB.println("Check the connector to RL03");
    while (1) {
      // Flash RED to indicate failure
      digitalWrite(CW01_RED, HIGH);
      delay(100);
      digitalWrite(CW01_RED, LOW);
      delay(100);
    }
  } else {
    // CR01 Initialized correctly
    //RL01.setModemConfig(RL01.Bw31_25Cr48Sf512);
    RL0X.setFrequency(RL03_FREQ);
    RL0X.setTxPower(23, false);
    RL0X.setThisAddress(ADDR_ID);
    RL0X.setHeaderFrom(FROM_ID);
    RL0X.setHeaderTo(TO_ID);
  }
  SerialUSB.println("setup done");
}

void loop() {
  SerialUSB.println("in loop");
  digitalWrite(CW01_BLUE,HIGH);
  
  if (RL0X.waitAvailableTimeout(1000)) {
    uint8_t start_seq[] = "[START]";
    
    
    uint8_t buf[sizeof(start_seq)];
    uint8_t len = sizeof(buf);

    SerialUSB.println("receiving start sequence");
      
    if (RL0X.recv(buf, &len)) {
      if(equalarrays(start_seq, buf, len))
      {
        SerialUSB.println("START SEQUENCE RECEIVED");
        myFile = SD.open(datafile, FILE_WRITE);
        while(RL0X.waitAvailableTimeout(3000))
        {
          SerialUSB.println("Receiving Packet");
          unsigned char packet [122];
          uint8_t pack_len = sizeof(packet);
           
          delay(400);
          String packetString;
          if(RL0X.recv(packet, &pack_len))
          {
            if(packet[0]=='S' && packet[121]=='E')
            {
              packetString = (char*)packet;
              myFile.println(packetString);
              SerialUSB.println(packetString);  
              uint8_t data[1] = {1};
              delay(100);
              RL0X.send(data, 1);
              SerialUSB.println("sending 1");
            }
            else
            {
              uint8_t data[1] = {0};
              delay(100);
              RL0X.send(data, 1);
              SerialUSB.println("Sending 0");
              packetString = (char*)packet;
              myFile.println(packetString);
              SerialUSB.println(packetString); 
            }
                  
          }
          //delay(100);
        }
        SerialUSB.println("file closed");
        myFile.close();
      }
      else
      {
        SerialUSB.println("Start sequence not received");
      }
    }    
    else {
      SerialUSB.println("[RADIO] receive failed");
    }
  }
  else
  {
    SerialUSB.println("[RADIO] Did not receive Start Sequence");
  }
  
  digitalWrite(CW01_BLUE,LOW);
}

bool equalarrays(uint8_t a[], uint8_t b[], uint8_t n)
{
  for (int i = 0; i < n; i++)
  {
    if (a[i] != b[i])
    {
      return false;
    }
  }
  return true;
}
