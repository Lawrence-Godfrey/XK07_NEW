
#include <xOD01.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266WiFiMulti.h>
#include <WiFiClient.h>
#include <ArduinoJson.h>

#include <WiFiClientSecureBearSSL.h>

xOD01 OD01;

String ssid, password;
ESP8266WiFiMulti WiFiMulti;

const uint8_t fingerprint[20] = {0xA8, 0xDB, 0xAA, 0x26, 0x38, 0x96, 0x0B, 0xD9, 0x49, 0x67, 0x11, 0xF1, 0x4D, 0xE1, 0xCE, 0x29, 0x26, 0xE8, 0xBA, 0x75};


void setup()
{
    Wire.begin();
    OD01.begin();
    Serial.begin(115200);
    ssid = "XinaBox";
    password = "RapidIoT";

    WiFi.mode(WIFI_STA);
    WiFiMulti.addAP(ssid.c_str(), password.c_str());
    
    int count {1};

    OD01.clear();
    OD01.set2X();
    OD01.println("Connecting ");
    OD01.println(" to WiFi...");
    OD01.println("");
    OD01.set1X();
    while (WiFiMulti.run() != WL_CONNECTED) {
      digitalWrite(LED_RED, HIGH);
      
      OD01.println("   .   ");
      delay(250);
      digitalWrite(LED_RED, LOW);
      delay(250);
      digitalWrite(LED_RED, HIGH);
      OD01.clear(0,128,6,8);
      OD01.println("   .   .   ");
      delay(250);
      digitalWrite(LED_RED, LOW);
      delay(250);
      digitalWrite(LED_RED, HIGH);
      OD01.clear(0,128,6,8);
      OD01.println("   .   .   .   ");
      delay(250);
      digitalWrite(LED_RED, LOW);
      delay(250);
      digitalWrite(LED_RED, HIGH);
      OD01.clear(0,128,6,8);
      OD01.println("   .   .   .   .");
      delay(250);
      digitalWrite(LED_RED, LOW);
      delay(250);
      OD01.clear(0,128,6,8);

      if(count>30)     //times out after 1 minute
      {
        OD01.clear();
        OD01.println("");
        OD01.println("");
        OD01.println("  Could not connect ");
        OD01.println("       to WiFi");
        OD01.println("");
        OD01.println("   Please try again");
        return;
      }
      count++;
      
    }
    
    OD01.clear();
    OD01.println("sending request...");

    
  
}

void loop() {

    int start_millis =millis;
    HTTPClient http;

    std::unique_ptr<BearSSL::WiFiClientSecure>client(new BearSSL::WiFiClientSecure);

    client->setFingerprint(fingerprint);
    
    Serial.print("[HTTP] begin...\n");
    if (http.begin(*client, "https://freegeoip.app/json/")) 
    {  // HTTP
    //   http.addHeader("accept", "application/json"); 
    //   http.addHeader("content-type", "application/json");
      Serial.print("[HTTP] GET...\n");
      // start connection and send HTTP header
      int httpCode = http.GET();

      // httpCode will be negative on error
      if (httpCode > 0) {
        // HTTP header has been send and Server response header has been handled
        Serial.printf("[HTTP] GET... code: %d\n", httpCode);
        // for(int i = 0; i< http.headers(); i++){
        //         Serial.println(http.header(i));
        //       }
        // file found at server
        if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) 
        {
          Serial.println("test 1");
//          String headerDate = http.header("latitude");
//          Serial.println(headerDate);                     
     
          String payload = http.getString();  
         // Serial.println(payload);
          
//          const size_t bufferSize = size;
          DynamicJsonBuffer jsonBuffer;
          JsonObject& root = jsonBuffer.parseObject(payload);
          
          String lat = root["latitude"];
          String longi = root["longitude"];

          Serial.println(lat);
          Serial.println(longi);
          
          

          

          

        }
      }
      else {
        Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
      }
      }
    else {
      Serial.printf("[HTTP} Unable to connect\n");
    }

    delay(60000);
}
