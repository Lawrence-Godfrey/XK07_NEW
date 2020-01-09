
#include <xOD01.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

xOD01 OD01;

String ssid, password;


void setup()
{
    Wire.begin();
    OD01.begin();
    Serial.begin(115200);
    ssid = "XinaBox";
    password = "RapidIoT";

    WiFi.begin(ssid.c_str(), password.c_str());
    int count {1};
    OD01.clear();
    OD01.set2X();
    OD01.println("Connecting ");
    OD01.println(" to WiFi...");
    OD01.println("");
    OD01.set1X();
    while (WiFi.status() != WL_CONNECTED) {
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
 
    if (WiFi.status() == WL_CONNECTED) { //Check WiFi connection status
    
        HTTPClient http;  //Declare an object of class HTTPClient
        
        http.begin("https://freegeoip.app/json/");  //Specify request destination
        int httpCode = http.GET();                                                                  //Send the request
        
        if (httpCode > 0) { //Check the returning code
            String payload = http.getString();   //Get the request response payload
            Serial.println(payload);                     //Print the response payload
        }
    
    http.end();   //Close connection
    }
 
delay(30000);    //Send a request every 30 seconds
 
}
