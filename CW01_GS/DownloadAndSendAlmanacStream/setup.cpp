void BEGIN_ALL()
{
  Serial.begin(115200);
  Wire.begin();
  OD01.begin();
  OD01.clear();
  
  for (uint8_t t = 4; t > 0; t--) {
    Serial.printf("[SETUP] WAIT %d...\n", t);
    Serial.flush();
    delay(1000);
  }

  if (!RL0X.begin()) { // <-- enter radio name here
    Serial.println("Check the connector to CR01");
    while (1) {
      // Flash RED to indicate failure
    delay(100);
  }
  } 
  else 
  {
    // RL0X Initialized correctly
    //RL0X.setModemConfig(RL01.Bw31_25Cr48Sf512);
    RL0X.setFrequency(RL03_FREQ);
    RL0X.setTxPower(23, false);
    RL0X.setThisAddress(RADIO_ID);
    RL0X.setHeaderFrom(RADIO_ID);
    RL0X.setHeaderTo(RADIO_ID); 
  }

}

void SETUP_WIFI()
{
  WiFi.mode(WIFI_STA);
  WiFiMulti.addAP(SSID, password);

  // wait for WiFi connection
  while((WiFiMulti.run() != WL_CONNECTED))
  {
    Serial.println(" . ");
    delay(500);
  }
}

bool CONNECT_TO_UBLOX()
{
  if ((WiFiMulti.run() == WL_CONNECTED)) 
  {
    WiFiClient client;

    HTTPClient http;

    Serial.print("[HTTP] begin...\n");
    if (http.begin(client, UBLOX_URL) || http.begin(client, UBLOX_URL_BACKUP))   //TODO add latency tag?
    {
      return 1;
    }
    else
    {
      Serial.println("[HTTP] Unable to connect to UBlox API");
      return 0;
    }
  }
  else
  {
    Serial.println("[WiFi] Could not connect to wifi");
    return 0;
  }
}

bool SEND_GET_REQUEST()
{
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
      return 1;
    }
    else
    {
      Serial.println("[HTTP] File not found on server");
      return 0;
    }
    
  }
  else 
  {
    Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
    return 0;
  }
}

uint8_t[] GET_ALMANAC()
{

}

bool RESEND_PACKET()
{
  uint8_t check[1];
  uint8_t len = 1;

  if (RL0X.waitAvailableTimeout(3000)) {
    if (RL0X.recv(check, &len)) {
      Serial.print("got reply: ");
      if(check[0]==0)
      {
        return 0;
        OD01.println("Resending packet");
        Serial.println("Resending Packet");
      }
      else if(check[0]==1)
      {
        return 1;
        OD01.println("Sending Next Packet");
        Serial.println("Sending next packet");
      }
    } else {
      Serial.println("[RADIO] Could not receive check bit");
    }
  }
}