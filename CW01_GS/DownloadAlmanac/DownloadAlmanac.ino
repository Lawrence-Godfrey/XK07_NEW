#include <Arduino.h>

#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>

#include <WiFiClient.h>
#include <xOD01.h>

#include <TinyGPS.h>

TinyGPS gps;

ESP8266WiFiMulti WiFiMulti;

xOD01 OD01;

//unsigned char ubx_nav_pvt_cmd[] = {0xB5, 0x62, 0x01, 0x07, 0x00, 0x00, 0x08, 0x19};

void setup() {

  Serial.begin(115200);
 // Serial.setDebugOutput(true);
  Wire.begin();
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
          String payload = http.getString();
          Serial.println(payload);
          Serial.print("Size: ");
          Serial.println(http.getSize());
          Wire.beginTransmission(0x42);
          Wire.write(payload.c_str());
          byte result = Wire.endTransmission();

          Serial.println(result);

//          Wire.beginTransmission(0x42);
//          for(int i = 0; i<8; i++)
//          {
//            Wire.write(ubx_nav_pvt_cmd[i]);
//          }
//          Serial.println(Wire.endTransmission());

          
          delay(2000);

          bool newData = false;
          unsigned long chars;
          unsigned short sentences, failed;
          
          Wire.requestFrom(0x42, 1);    // request 1 byte from slave device #2
          
          while(true)
          {
            char cc = Wire.read();
            Serial.print("character received: "); Serial.println(Wire.read());
            delay(10);
          }
          while(Wire.available())    // slave may send less than requested
          { 
            Serial.println("wire dot available");
            char c = Wire.read();

            Serial.print(c);
            if (gps.encode(c)){
              Serial.println("gps dot encode");
              // Did a new valid sentence come in?
              newData = true;// receive a byte as character
              
            }
            else
            {
              Serial.println("could not encode");
            }

            Serial.println("out of while loop");
            
                     // print the character
            
          }
        
//          if (newData)
//          {
//            float flat, flon;
//            unsigned long age;
//            gps.f_get_position(&flat, &flon, &age);
//            Serial.print("LAT=");
//            Serial.println(flat == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : flat, 6);
//            Serial.print(" LON=");
//            Serial.println(flon == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : flon, 6);
//            Serial.print(" SAT=");
//            Serial.println(gps.satellites() == TinyGPS::GPS_INVALID_SATELLITES ? 0 : gps.satellites());
//            Serial.print(" PREC=");
//            Serial.println(gps.hdop() == TinyGPS::GPS_INVALID_HDOP ? 0 : gps.hdop());
//          }
//          
//          gps.stats(&chars, &sentences, &failed);
//         // Serial.print(" CHARS=");
//         //Serial.print(chars);
//         // Serial.print(" SENTENCES=");
//         // Serial.print(sentences);
//         // Serial.print(" CSUM ERR=");
//         // Serial.println(failed);
//          if (chars == 0)
//            Serial.println("** No characters received from GPS: check wiring **");
        }
      } else {
        Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
      }

      http.end();
    }
    else if(http.begin(client, "http://online-live2.services.u-blox.com/GetOnlineData.ashx?token=SjneqlMN-UG2zAzl_Egmdw;gnss=gps;datatype=eph,alm,aux,pos;filteronpos;format=aid"))
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
  else
    Serial.println("could not connect to wifi");

 
  delay(120000);
}
