#include <Arduino.h>

#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>

#include <WiFiClient.h>

ESP8266WiFiMulti WiFiMulti;

void setup() {

  Serial.begin(115200);
 // Serial.setDebugOutput(true);
  Wire.begin();

  for (uint8_t t = 4; t > 0; t--) {
    Serial.printf("[SETUP] WAIT %d...\n", t);
    Serial.flush();
    delay(1000);
  }

  WiFi.mode(WIFI_STA);
  WiFiMulti.addAP("XinaBox", "RapidIoT");
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
          uint8_t buff[128] = {};

          WiFiClient * stream = &client;

          // read all data from server
          while (http.connected() && (len > 0 || len == -1)) {
            // read up to 128 byte
            int c = stream->readBytes(buff, std::min((size_t)len, sizeof(buff)));
            Serial.printf("readBytes: %d\n", c);
            if (!c) {
              Serial.println("read timeout");
            }

            // write it to Serial
            Serial.write(buff, c);

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
