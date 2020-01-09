


#include <ArduinoJson.h>    // https://github.com/bblanchon/ArduinoJson
#include <xProvision.h>     // https://github.com/xinabox/arduino-Provision    
#include <xOD01.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>


xProvision prv;
xOD01 OD01;

String ssid, password, unit_name;
const char* host = "www.google.com";
const uint16_t port = 80;

const char* host_gps = "www.agps.u-blox.com";
const uint16_t port_gps = 46434;

void setup() {
  // Set RGB Pins as outputs
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_RED, OUTPUT);
  delay(10000);
  Wire.begin();
  OD01.begin();
 // Serial.begin(115200);
  prv.begin();

  //prv.formatMemory();
  
  prv.addWiFi();
  prv.addVariable("Unit Name:", "Choose a name for your XK07");

  prv.transmit();
  prv.receive();


  if (prv.success())
  {
    prv.getWiFi(ssid, password);
    WiFi.begin(ssid.c_str(), password.c_str());

    prv.getVariable("Unit Name:", unit_name);

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

    digitalWrite(LED_RED, LOW);
    digitalWrite(LED_GREEN, HIGH);
    OD01.set1X();
    OD01.clear();
    OD01.println("   WiFi Connected");
    OD01.println("");
    OD01.println("  Checking Internet");
    OD01.println("    Connection...");
    
    WiFiClient client;
    if (!client.connect(host, port)) {
      Serial.println("connection failed");
      OD01.clear();
      OD01.println("Could Not Connect ");
      OD01.println("   to Internet");
      OD01.println("Please check your");
      OD01.println("Internet Connection");
      OD01.println("  and try again");
      digitalWrite(LED_RED, HIGH);
      digitalWrite(LED_GREEN, LOW);
      return;
    }
    else
    {
      Serial.println("Connected");
      OD01.println("");
      OD01.println("Connected to Internet");
      OD01.println("");
      digitalWrite(LED_RED, LOW);
      digitalWrite(LED_GREEN, HIGH);
    }
    
  }
  else
  {
    prv.fail();
    OD01.println("Unable to get");
    OD01.println("  WiFi Data");
    digitalWrite(LED_RED, HIGH);
    digitalWrite(LED_GREEN, LOW);
    return;
  }
  
  delay(5000);
  OD01.clear();
  OD01.println("Unit Name:");
  OD01.print("    ");
  OD01.print(unit_name);


  getAlmanac();
  

}

void loop()
{
   
}
