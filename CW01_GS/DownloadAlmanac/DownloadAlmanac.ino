#include <Arduino.h>

#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>

#include <WiFiClient.h>
#include <xOD01.h>

ESP8266WiFiMulti WiFiMulti;

xOD01 OD01;

void setup() {

  Serial.begin(115200);
 // Serial.setDebugOutput(true);

  Serial.println();
  Serial.println();
  Serial.println();

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
  if ((WiFiMulti.run() == WL_CONNECTED)) {

    WiFiClient client;

    HTTPClient http;

    Serial.print("[HTTP] begin...\n");
    if (http.begin(client, "http://online-live1.services.u-blox.com/GetOnlineData.ashx?token=SjneqlMN-UG2zAzl_Egmdw;gnss=gps;datatype=eph,alm,aux,pos;filteronpos;format=aid;lat=-33.9258;lon=18.4259;pacc=5000")) 
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
          String payload = http.getString();
          Serial.println(payload);
          
        }
      } else {
        Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
      }

      http.end();
    }
    else if(http.begin(client, "http://online-live2.services.u-blox.com/GetOnlineData.ashx?token=SjneqlMN-UG2zAzl_Egmdw;gnss=gps;datatype=eph,alm,aux,pos;filteronpos;format=aid;lat=-33.9258;lon=18.4259;pacc=5000"))
    {
      Serial.print("Live 2");
      Serial.print("[HTTP] GET...\n");
      // start connection and send HTTP header
      int httpCode = http.GET();

      // httpCode will be negative on error
      if (httpCode > 0) {
        // HTTP header has been send and Server response header has been handled
        Serial.printf("[HTTP] GET... code: %d\n", httpCode);

        // file found at server
        if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) {
          String payload = http.getString();
          Serial.println(payload);
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

 
  delay(120000);
}