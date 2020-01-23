void sendAlmanacFile()
{
  //Get Almanac file from SD card
  if (SD.exists(datafile))
  {
    SerialUSB.println("File found");
  }
  else {
    
    SerialUSB.println("File doesn't exist");
    
  }

  File almanac = SD.open(datafile);

  if (almanac)
  {
    Wire.beginTransmission(0x42);
    while (almanac.available())
    {
      Wire.write(almanac.read());
      SerialUSB.print("Bytes Remaining: ");
      SerialUSB.println(almanac.available());
      //delay(1);
    }
    Wire.endTransmission();
    almanac.close();
  }

  delay(3000);
  
  SerialUSB.println("File uploaded");  
}

void getGPSData()
{
  bool newData = false;
  unsigned long chars;
  unsigned short sentences, failed;

  Wire.requestFrom(0x42, 1);    // request 1 byte from SN01

  while (Wire.available())   // slave may send less than requested
  {
    char c = Wire.read();
    //SerialUSB.print(c);
    if (gps.encode(c)) // Did a new valid sentence come in?
      newData = true;// receive a byte as character
    // Serial.print(c);         // print the character
  }

  if (newData)
  {
    if (! bme.performReading()) {
      Serial.println("Failed to perform reading :(");
      return;
    }

    //lat, lon, alt and speed
    gps.f_get_position(&flat, &flon, &age);
    gps.crack_datetime(&year, &month, &day,
                       &hour, &minutes, &seconds, &hundredths, &fix_age);

    splitIntoDMS(flat, latDegs, latMins, latSecs);
    splitIntoDMS(flng, lngDegs, lngMins, lngSecs);

    falt = gps.f_altitude(); // +/- altitude in meters
    fkmph = gps.f_speed_kmph(); // speed in km/
    HDOP = gps.hdop();

    SerialUSB.print("latitude: "); SerialUSB.println(flat, 6);
    SerialUSB.print("Longitude: "); SerialUSB.println(flon, 6);
    SerialUSB.print("Altitude(m): "); SerialUSB.println(falt);
    SerialUSB.print("Speed(kmph) "); SerialUSB.println(fkmph);
}