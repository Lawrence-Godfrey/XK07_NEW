#include <ArduinoJson.h>    // https://github.com/bblanchon/ArduinoJson
#include <xProvision.h>     // https://github.com/xinabox/arduino-Provision    
#include <xOD01.h>

xProvision prv;
xOD01 OD01;

String ssid, password, unit_name;
const char* host = "www.google.com";
const uint16_t port = 80;

void setup() {
  // Set RGB Pins as outputs
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_RED, OUTPUT);

  Wire.begin();
  OD01.begin();

  prv.begin();
  prv.addWiFi();
  prv.addVariable("Unit Name:", "Choose a name for your XK07")

  prv.transmit();
  prv.receive();


  if (prv.success())
  {
    prv.getWiFi(ssid, password);
    WiFi.begin(ssid.c_str(), password.c_str());

    prv.getVariable("Unit Name:", unit_name);

    int count {1};
    OD01.clear();
    OD01.println("Connecting to WiFi...");
    OD01.println("");
    

    while (WiFi.status() != WL_CONNECTED) {
      digitalWrite(LED_RED, HIGH);
      OD01.println(".  .  .  .");      
      OD01.clear(32*(1+(count%4)),128,2,6);
      delay(250);
      digitalWrite(LED_RED, LOW);
      delay(250);
      count++;
    }

    digitalWrite(LED_RED, LOW);
    digitalWrite(LED_GREEN, HIGH);
    OD01.set1X();
    OD01.clear()
    OD01.println("Connected");
    OD01.println("Checking Internet");
    OD01.println("   Connection...")
    
    WiFiClient client;
    if (!client.connect(host, port)) {
      Serial.println("connection failed");
      OD01.clear();
      OD01.println("Could Not Connect ");
      OD01.println("   to Internet");
      OD01.println("Please check your");
      OD01.println("Internet Connection");
      OD01.println("  and try again")
      digitalWrite(LED_RED, HIGH);
      digitalWrite(LED_GREEN, LOW);
      delay(5000);
      return;
    }
    else
    {
      Serial.println("Connected");
    }
    digitalWrite(LED_RED, LOW);
    digitalWrite(LED_GREEN, HIGH);
  }
  else
  {
    prv.fail();
    OD01.println("Unable to get");
    OD01.println("  WiFi Data");
    digitalWrite(LED_RED, HIGH);
    digitalWrite(LED_GREEN, LOW);
  }
}

void loop()
{
   
}
