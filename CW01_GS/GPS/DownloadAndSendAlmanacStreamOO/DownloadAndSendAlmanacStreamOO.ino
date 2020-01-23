#include <Arduino.h>

#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>

#include <WiFiClient.h>
#include <xOD01.h>

#include <TinyGPS.h>

#include <xRL0x.h>

#include "DownloadAndSend.h"

TinyGPS gps;

ESP8266WiFiMulti WiFiMulti;

xOD01 OD01;

void setup() {
  BEGIN_ALL();
  SETUP_WIFI();
}

void loop() {
  
  
  if(CONNECT_TO_UBLOX() && SEND_GET_REQUEST())
  {
    // get lenght of document (is -1 when Server sends no Content-Length header)
    int len = http.getSize();

    // create buffer for read
    uint8_t buff[BUFFER_SIZE] = {0};

    WiFiClient * stream = &client;

    Serial.println("Sending to RL0X Server");

    uint8_t start_seq[] = "[START]";
    //delay(100);
    RL0X.send(start_seq, sizeof(start_seq));
    
    
    // read all data from server
    while (http.connected() && (len > 0 || len == -1)) {
      size_t c;
      
      lastPacketSuccesfull = false;
      
      // read up to 128 byte
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
        packet = (uint8_t*) malloc (c+2+1);
        
        std::copy(buff + 0, buff + c, packet + 1);
        packet[0] = 'S';
        packet[c+1] = 'E';

        //packet = (uint8_t*)"SThis is a test iiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiThis is a testE";
        
        Serial.println();
        Serial.write(packet, c+2);
        Serial.println();
        Serial.println("size: ");Serial.print(c+2);
        Serial.println();

        
        delay(100);
        
        RL0X.send(packet, BUFFER_SIZE+2);
        
        lastPacketSuccesfull = RESEND_PACKAGE;


        } else {
          Serial.println("[RADIO] Nothing received, is the Flight Station Running?");
        }
         free(packet);
      }

      if (len > 0) {
        len -= c;
      }
    }
  }
  
  http.end();
    
  delay(120000);
}
