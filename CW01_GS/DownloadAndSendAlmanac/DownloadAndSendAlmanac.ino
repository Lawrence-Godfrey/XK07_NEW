#include <Arduino.h>

#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>

#include <WiFiClient.h>
#include <xOD01.h>

#include <TinyGPS.h>

#include <xRL0x.h>

TinyGPS gps;

ESP8266WiFiMulti WiFiMulti;

xOD01 OD01;

#define RL03_FREQ 915.0

// Radio Address
#define ADDR_ID 0x31
#define FROM_ID 0x31
#define TO_ID   0x11

//unsigned char ubx_nav_pvt_cmd[] = {0xB5, 0x62, 0x01, 0x07, 0x00, 0x00, 0x08, 0x19};

bool lastPacketSuccesfull;

void setup() {

  Serial.begin(115200);
 // Serial.setDebugOutput(true);
  Wire.begin();
  Serial.println();
  Serial.println();
  Serial.println();

  OD01.begin();
  OD01.clear();
  for (uint8_t t = 4; t > 0; t--) {
    Serial.printf("[SETUP] WAIT %d...\n", t);
    Serial.flush();
    delay(1000);
  }

  WiFi.mode(WIFI_STA);
  WiFiMulti.addAP("XinaBox", "RapidIoT");

  if (!RL0X.begin()) { // <-- enter radio name here
    Serial.println("Check the connector to CR01");
    while (1) {
      // Flash RED to indicate failure
    delay(100);
  }
  } 
  else 
  {
    // RL0X Initialized correctly
    //RL0X.setModemConfig(RL01.Bw31_25Cr48Sf512);
    RL0X.setFrequency(RL03_FREQ);
    RL0X.setTxPower(23, false);
  }
}

void loop() {
  // wait for WiFi connection
  while((WiFiMulti.run() != WL_CONNECTED))
  {
    Serial.println(" . ");
    delay(500);
  }
  
  if ((WiFiMulti.run() == WL_CONNECTED)) {

    WiFiClient client;

    HTTPClient http;

    Serial.print("[HTTP] begin...\n");
    if (http.begin(client, "http://online-live1.services.u-blox.com/GetOnlineData.ashx?token=SjneqlMN-UG2zAzl_Egmdw;gnss=gps;datatype=eph,alm,aux,pos;filteronpos;format=aid")) 
    {  // HTTP


      Serial.print("[HTTP] GET...\n");
      // start connection and send HTTP header
      int httpCode = http.GET();

      // httpCode will be negative on error
      if (httpCode > 0) {
        // HTTP header has been send and Server response header has been handled
        Serial.printf("[HTTP] GET... code: %d\n", httpCode);

        // file found at server
        if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) 
        {
          String payload = "This is a test"
                            "Definitely a test"
                            "nothing more than a test"
                            "just testing if everything works and now this is a long sentence that i'm testing and its being tested and its long"
                            "This is a test 2"
                            "Definitely a test"
                            "nothing more than a test"
                            "just testing if everything works and now this is a long sentence that i'm testing and its being tested and its long"
                            "This is a test 3"
                            "Definitely a test"
                            "nothing more than a test"
                            "just testing if everything works and now this is a long sentence that i'm testing and its being tested and its long"
                            "This is a test 4"
                            "Definitely a test"
                            "nothing more than a test"
                            "just testing if everything works and now this is a long sentence that i'm testing and its being tested and its long";
          Serial.println(payload);
          int alm_size = payload.length(); 
          Serial.print("Size: ");
          Serial.println(alm_size);
          Serial.println("______________________________________________________");
          
          OD01.println("Downloaded Almanac");
          while(true)
          {
            OD01.println("Sending Almanac...");
            char almanac[alm_size + 1];
            const char* payloadc = payload.c_str();
            unsigned pos = 0;

//            while(pos < payload.length())
//            {
//              Serial.print(payloadc + pos);
//              Serial.print("n"); /*output whatever you want to represent a null character here*/;
//          
//              pos += strlen(payloadc) + 1;
//            }
    
            
            strcpy(almanac, payload.c_str());       
            
            Serial.println("Sending to RL0X Server");

            uint8_t start_seq[] = "[START]";
            delay(100);
            RL0X.send(start_seq, sizeof(start_seq));
            
            for(int i = 0; i < alm_size; i+=150)
            {
              lastPacketSuccesfull = false;
              while(!lastPacketSuccesfull)
              {
                uint8_t packet [102] {0};
                std::copy(almanac + i + 0, almanac + i + 150, packet + 1);
                packet[0] = 'S';
                packet[151] = 'E';

                Serial.println((char*)packet);

                delay(250);
                RL0X.send(packet, 152);
                
                uint8_t check[1];
                uint8_t len = sizeof(check);

                if (RL0X.waitAvailableTimeout(3000)) {
                  if (RL0X.recv(check, &len)) {
                    Serial.print("got reply: ");
                    if(check[0]=='0')
                    {
                      lastPacketSuccesfull = false;
                    }
                    else if(check[0]=='1')
                    {
                      lastPacketSuccesfull = true;
                    }
                    
                  } else {
                    Serial.println("recv failed");
                  }


                } else {
                  
                  Serial.println("No reply, is the RL01 server running ?");
                }
              }
                
            }

            uint8_t end_seq[] = "[END]";
            delay(100);
            RL0X.send(end_seq, sizeof(end_seq));
            

            

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

            
            
            delay(20000);
          }
        }
      } else {
        Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
      }

      http.end();
    }
    
    else {
      Serial.printf("[HTTP} Unable to connect\n");
    }
  }
  else
    Serial.println("could not connect to wifi");

 
  delay(120000);
}
