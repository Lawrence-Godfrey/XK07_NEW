void getAlmanac()
{
    OD01.clear();
    OD01.println("sending request...");
    delay(1000);
    HTTPClient http;
    OD01.println("test 1");
    delay(1000);
    // Paste below ublox almanac downloading link
    http.begin("http://online-live1.services.u-blox.com/GetOnlineData.ashx?token=60MHKSUo10q7ydnB5I9GgQ;gnss=gps;datatype=eph,alm,aux,pos;filteronpos;format=aid;lat=-33.9258;lon=18.4259;pacc=5000");
    OD01.println("test 2");
    delay(1000);
    // start connection and send HTTP header
    int httpCode = http.GET();
    if (httpCode > 0) {

      // file found at server
      if (httpCode == HTTP_CODE_OK) {

        // get lenght of document (is -1 when Server sends no Content-Length header)
        int len = http.getSize();

        // create buffer for read
        uint8_t buff[4000] = { 0 };

        // get tcp stream
        WiFiClient * stream = http.getStreamPtr();

        // read all data from server
        while (http.connected() && (len > 0 || len == -1)) {
          // get available data size
          size_t size = stream->available();

          if (size) {
            // read bytes
            int c = stream->readBytes(buff, ((size > sizeof(buff)) ? sizeof(buff) : size));

            // write it to Serial
            Serial.write(buff, c);

            if (len > 0) {
              len -= c;
            }
          }
          delay(1);
        }

      }
    } else {
      Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
    }

    http.end();
}
