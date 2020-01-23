//String getIPlocation() { // Using freegeoip.net to map public IP's location
//  HTTPClient http;
//  String URL = "http://freegeoip.net/json/"; // no host or IP specified returns client's public IP info
//  String payload;
//  String loc;
//  http.setUserAgent(UserAgent);
//  if (!http.begin(URL)) {
//    Serial.println(F("getIPlocation: [HTTP] connect failed!"));
//  } else {
//    int stat = http.GET();
//    if (stat > 0) {
//      if (stat == HTTP_CODE_OK) {
//        payload = http.getString();
//        DynamicJsonBuffer jsonBuffer;
//        JsonObject& root = jsonBuffer.parseObject(payload);
//        if (root.success()) {
//          String region = root["region_name"];
//          String country = root["country_code"];
//          String lat = root["latitude"];
//          String lng = root["longitude"];
//          loc = lat + "," + lng;
//          Serial.println("getIPlocation: " + region + ", " + country);
//        } else {
//          Serial.println(F("getIPlocation: JSON parse failed!"));
//          Serial.println(payload);
//        }
//      } else {
//        Serial.printf("getIPlocation: [HTTP] GET reply %d\r\n", stat);
//      }
//    } else {
//      Serial.printf("getIPlocation: [HTTP] GET failed: %s\r\n", http.errorToString(stat).c_str());
//    }
//  }
//  http.end();
//  return loc;
//} // getIPlocation
