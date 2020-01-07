#include <ArduinoJson.h>    // https://github.com/bblanchon/ArduinoJson
#include <xProvision.h>     // https://github.com/xinabox/arduino-Provision    
#include <xOD01.h>

xProvision prv;
xOD01 OD01;

String ssid, password;

void setup() {
  // Set RGB Pins as outputs
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_RED, OUTPUT);

    Wire.begin();
  OD01.begin();

  // put your setup code here, to run once:
  prv.begin();
  prv.addWiFi();

  prv.transmit();
  //Writes this string, with the CRLF and SYNC prefixed and CRLF suffixed
  //$!${"WiFi_Network":"Your SSID","WiFi_Password":"Your PSK"}

  prv.receive();
  //Reads this string, with CRLF suffixed
  //{"WiFi_Network":"Your-SSID","WiFi_Password":"Your-PSK"}

  if (prv.success())
  {
    prv.getWiFi(ssid, password);
    WiFi.begin(ssid.c_str(), password.c_str());

    while (WiFi.status() != WL_CONNECTED) {
      digitalWrite(LED_RED, HIGH);
      delay(250);
      digitalWrite(LED_RED, LOW);
      delay(250);
    }
    OD01.println(ssid);
    OD01.println("IP address: ");
    OD01.println(WiFi.localIP());
    OD01.println(password);
    digitalWrite(LED_GREEN, HIGH);
  }
  else
  {
    prv.fail();
  }
}

void loop()
{
  prv.transmit();
  //Writes this string, with the CRLF and SYNC prefixed and CRLF suffixed
  //$!${"WiFi_Network":"Your SSID","WiFi_Password":"Your PSK"}

  prv.receive();
  //Reads this string, with CRLF suffixed
  //{"WiFi_Network":"Your-SSID","WiFi_Password":"Your-PSK"}

  if (prv.success())
  {
    prv.getWiFi(ssid, password);
    WiFi.begin(ssid.c_str(), password.c_str());

    while (WiFi.status() != WL_CONNECTED) {
      digitalWrite(LED_RED, HIGH);
      delay(250);
      digitalWrite(LED_RED, LOW);
      delay(250);
    }
    OD01.println(ssid);
    OD01.println("IP address: ");
    OD01.println(WiFi.localIP());
    OD01.println(password);
    digitalWrite(LED_GREEN, HIGH);
    
  }
  else
  {
    prv.fail();
    Serial.println("PRV FAIL");
  }

  delay(5000);

  
}
