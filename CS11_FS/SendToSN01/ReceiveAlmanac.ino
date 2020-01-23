#include <xCore.h>
#include <xRL0x.h>
#include <xCS11_SDU.h>
#include <SD.h>

#include <TinyGPS.h>


#define CW01_RED 11
#define CW01_GREEN 12
#define CW01_BLUE 4
  
// Radio Address
#define RADIO_ID 0x11;
#define RL03_FREQ 915.0;

File myFile;
char[] datafile;

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
    RL0X.setFrequency(RL03_FREQ);
    RL0X.setTxPower(23, false);
    RL0X.setThisAddress(RADIO_ID);
    RL0X.setHeaderFrom(RADIO_ID);
    RL0X.setHeaderTo(RADIO_ID);
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
          uint8_t packet [123];
          uint8_t pack_len = 123;
           
          delay(100);

          if(RL0X.recv(packet, &pack_len))
          {
            size_t data_length = packet[0];
            if(packet[1]=='S' && packet[data_length+2]=='E')
            {
              
              for (size_t i = 2; i < data_length+2; i++)
              {
                myFile.write(packet[i]);
              }

              SerialUSB.write(packet,123);
              SerialUSB.println();
              SerialUSB.print("data length:  "); SerialUSB.println(data_length);  

              uint8_t data[1] {1};
              RL0X.send(data, 1);
              SerialUSB.println("sending 1");
            }
            else
            {
              uint8_t data[1] {0};
              SerialUSB.write(packet, 123); 
              RL0X.send(data, 1);
              SerialUSB.println("Sending 0");
            }
          }
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
