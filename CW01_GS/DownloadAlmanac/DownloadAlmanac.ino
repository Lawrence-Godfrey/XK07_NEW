#include <xOD01.h>
#include <ESP8266WiFi.h>

xOD01 OD01;

String ssid, password;

uint8_t almanac_data[];

const char* host = "www.agps.u-blox.com";
const uint16_t port = 46434;

void setup()
{
    Wire.begin();
    OD01.begin();
    OD01.prinln("Getting GPS Data...");

    ssid = "XinaBox";
    password = "RapidIoT";

    WiFiClient client;
    if (!client.connect(host, port)) {             //Check if can connect to host
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

    }
    OD01.clear();
    OD01.println("sending request...");

    // try and send request for data. 
    if (client.connected()) {                                 
        client.println("https://online-live1.services.u-blox.com/GetOnlineData.ashx?token=XXXXXXXXXXXXXXXXXXXXXX;gnss=gps,glo;datatype=eph,alm,aux;");
    }


    // wait for data to be available
    unsigned long timeout = millis();
    while (client.available() == 0) {
        if (millis() - timeout > 5000) {
            Serial.println(">>> Client Timeout !");
            client.stop();
            delay(60000);
            return;
    }
  }

  while (client.available()) {
    char ch = static_cast<char>(client.read());
    Serial.print(ch);
  }

  Serial.println();
  Serial.println("closing connection");
  client.stop();
}

void loop()
{
   
}