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

// Radio Address
const uint8_t RADIO_ID {0x11};
const float RL03_FREQ {915.0};

bool lastPacketSuccesfull;

void setup() {

  Serial.begin(115200);
 // Serial.setDebugOutput(true);
  Wire.begin();

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
    RL0X.setThisAddress(RADIO_ID);
    RL0X.setHeaderFrom(RADIO_ID);
    RL0X.setHeaderTo(RADIO_ID); 
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
    if (http.begin(client, "http://online-live1.services.u-blox.com/GetOnlineData.ashx?token=SjneqlMN-UG2zAzl_Egmdw;gnss=gps;datatype=eph,alm,aux,pos;filteronpos;format=aid"))   //TODO add latency tag? Add second server request 
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
          // get lenght of document (is -1 when Server sends no Content-Length header)
          int len = http.getSize();

          // create buffer for read
          uint8_t buff[120] = {0};

          WiFiClient * stream = &client;

          Serial.println("Sending to RL0X Server");

          uint8_t start_seq[] = "[START]";
          //delay(100);
          RL0X.send(start_seq, sizeof(start_seq));
          
          
          // read all data from server
          while (http.connected() && (len > 0 || len == -1)) {
            size_t c;
            
            lastPacketSuccesfull = false;
            
            // read up to 120 bytes
            c = stream->readBytes(buff, std::min((size_t)len, sizeof(buff)));
            Serial.printf("readBytes: %d\n", c);
            if (!c) {
              Serial.println("read timeout");
            }
            
            while(!lastPacketSuccesfull)
            {
              // write it to Serial
              Serial.write(buff, c);


              uint8_t * packet;
              packet = (uint8_t*) malloc (c+3+1);
              
              std::copy(buff + 0, buff + c, packet + 2);
              packet[0] = c;
              packet[1] = 'S';
              packet[c+2] = 'E';

              //packet = (uint8_t*)"SThis is a test iiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiThis is a testE";
              
              Serial.println();
              Serial.write(packet, c+3);
              Serial.println();
              Serial.println("size: ");Serial.print(c+3);
              Serial.println();

              
              delay(100);
              
              RL0X.send(packet, 123);
              
              uint8_t check[1];
              uint8_t len = 1;

              if (RL0X.waitAvailableTimeout(3000)) {
                if (RL0X.recv(check, &len)) {
                  Serial.print("got reply: ");
                  if(check[0]==0)
                  {
                    OD01.println("Resending packet");
                    Serial.println("Resending Packet");
                    lastPacketSuccesfull = false;
                  }
                  else if(check[0]==1)
                  {
                    lastPacketSuccesfull = true;
                    Serial.println("Sending next packet");
                  }
                  else
                  {
                    Serial.println("neither");
                  }
                  
                } else {
                  Serial.println("[RADIO] Could not receive check bit");
                }


              } else {
                Serial.println("[RADIO] Nothing received, is the Flight Station Running?");
              }
             // free(packet);
            }

            if (len > 0) {
              len -= c;
            }
          }
        }
      } else {
        Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
      }

      http.end();
    }
    else {
      Serial.printf("[HTTP] Unable to connect to UBlox API\n");
    }
  }
  else
    Serial.println("[WiFi] Could not connect to wifi");

 
  delay(120000);
}
