
#include <xOD01.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266WiFiMulti.h>
#include <WiFiClient.h>


xOD01 OD01;

String ssid, password;
ESP8266WiFiMulti WiFiMulti;

const char* root_ca= \
"-----BEGIN CERTIFICATE-----\n" \
"MIIDnzCCAyWgAwIBAgIQWyXOaQfEJlVm0zkMmalUrTAKBggqhkjOPQQDAzCBhTEL\n" \
"MAkGA1UEBhMCR0IxGzAZBgNVBAgTEkdyZWF0ZXIgTWFuY2hlc3RlcjEQMA4GA1UE\n" \
"BxMHU2FsZm9yZDEaMBgGA1UEChMRQ09NT0RPIENBIExpbWl0ZWQxKzApBgNVBAMT\n" \
"IkNPTU9ETyBFQ0MgQ2VydGlmaWNhdGlvbiBBdXRob3JpdHkwHhcNMTQwOTI1MDAw\n" \
"MDAwWhcNMjkwOTI0MjM1OTU5WjCBkjELMAkGA1UEBhMCR0IxGzAZBgNVBAgTEkdy\n" \
"ZWF0ZXIgTWFuY2hlc3RlcjEQMA4GA1UEBxMHU2FsZm9yZDEaMBgGA1UEChMRQ09N\n" \
"T0RPIENBIExpbWl0ZWQxODA2BgNVBAMTL0NPTU9ETyBFQ0MgRG9tYWluIFZhbGlk\n" \
"YXRpb24gU2VjdXJlIFNlcnZlciBDQSAyMFkwEwYHKoZIzj0CAQYIKoZIzj0DAQcD\n" \
"QgAEAjgZgTrJaYRwWQKOqIofMN+83gP8eR06JSxrQSEYgur5PkrkM8wSzypD/A7y\n" \
"ZADA4SVQgiTNtkk4DyVHkUikraOCAWYwggFiMB8GA1UdIwQYMBaAFHVxpxlIGbyd\n" \
"nepBR9+UxEh3mdN5MB0GA1UdDgQWBBRACWFn8LyDcU/eEggsb9TUK3Y9ljAOBgNV\n" \
"HQ8BAf8EBAMCAYYwEgYDVR0TAQH/BAgwBgEB/wIBADAdBgNVHSUEFjAUBggrBgEF\n" \
"BQcDAQYIKwYBBQUHAwIwGwYDVR0gBBQwEjAGBgRVHSAAMAgGBmeBDAECATBMBgNV\n" \
"HR8ERTBDMEGgP6A9hjtodHRwOi8vY3JsLmNvbW9kb2NhLmNvbS9DT01PRE9FQ0ND\n" \
"ZXJ0aWZpY2F0aW9uQXV0aG9yaXR5LmNybDByBggrBgEFBQcBAQRmMGQwOwYIKwYB\n" \
"BQUHMAKGL2h0dHA6Ly9jcnQuY29tb2RvY2EuY29tL0NPTU9ET0VDQ0FkZFRydXN0\n" \
"Q0EuY3J0MCUGCCsGAQUFBzABhhlodHRwOi8vb2NzcC5jb21vZG9jYTQuY29tMAoG\n" \
"CCqGSM49BAMDA2gAMGUCMQCsaEclgBNPE1bAojcJl1pQxOfttGHLKIoKETKm4nHf\n" \
"EQGJbwd6IGZrGNC5LkP3Um8CMBKFfI4TZpIEuppFCZRKMGHRSdxv6+ctyYnPHmp8\n" \
"7IXOMCVZuoFwNLg0f+cB0eLLUg==\n" \
"-----END CERTIFICATE-----\n";


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
 
    WiFiClient client;
    HTTPClient http;

    Serial.print("[HTTP] begin...\n");
    if (http.begin(client, "https://freegeoip.app/json/")) 
    {  // HTTP
      http.addHeader("accept", "application/json"); 
      http.addHeader("content-type", "application/json");
      Serial.print("[HTTP] GET...\n");
      // start connection and send HTTP header
      int httpCode = http.GET();

      // httpCode will be negative on error
      if (httpCode > 0) {
        // HTTP header has been send and Server response header has been handled
        Serial.printf("[HTTP] GET... code: %d\n", httpCode);
        for(int i = 0; i< http.headers(); i++){
                Serial.println(http.header(i));
              }
        // file found at server
        if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) 
        {
          Serial.println("test 1");
//          String headerDate = http.header("latitude");
//          Serial.println(headerDate);                     
     
          String payload = http.getString();  
          Serial.println(payload);

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
