void logdata(int index, float data) {
  // Log To SD Card
  if (SD_CARD_INITIALIZED) {
    if (DataFile) {
      DataFile.print(data);
      DataFile.print("  ");
      DataFile.print(units[index]);
      DataFile.print(",");
    }
  }
}

void logdata(int index, int data) {
  // Log To SD Card
  if (SD_CARD_INITIALIZED) {
    if (DataFile) {
      DataFile.print(data);
      DataFile.print("  ");
      DataFile.print(units[index]);
      DataFile.print(",");
    }
  }
}

void logdata(int index, long data) {
  // Log To SD Card
  if (SD_CARD_INITIALIZED) {
    if (DataFile) {
      DataFile.print(data);
      DataFile.print("  ");
      DataFile.print(units[index]);
      DataFile.print(",");
    }
  }
}

void logdata(int index, char data[]) {
  // Log To SD Card
  if (SD_CARD_INITIALIZED) {
    if (DataFile) {
      DataFile.print(data);
      if((sizeof(data)/sizeof(data[0])==0)){
        DataFile.print("  ");
        DataFile.print(units[index]);
      }
      DataFile.print(",");
    }
  }
}

void logdata(int index, uint32_t data) {
  // Log To SD Card
  if (SD_CARD_INITIALIZED) {
    if (DataFile) {
      DataFile.print(data);
      DataFile.print("  ");
      DataFile.print(units[index]);
      DataFile.print(",");
    }
  }
}

void logdata(int index, uint16_t data) {
  // Log To SD Card
  if (SD_CARD_INITIALIZED) {
    if (DataFile) {
      DataFile.print(data);
      DataFile.print("  ");
      DataFile.print(units[index]);
      DataFile.print(",");
    }
  }
}

void logdata(int index, String data) {
  // Log To SD Card
  if (SD_CARD_INITIALIZED) {
    if (DataFile) {
      DataFile.print(data);
      DataFile.print("  ");
      DataFile.print(units[index]);
      DataFile.print(",");
    }
  }
}

uint16_t CountDataFiles()
{
  uint16_t count = 0;
  if (SD_CARD_INITIALIZED) {
    String tempfile;
    tempfile = DataFolder + "/DATA" + String(count) + ".CSV";
    SerialUSB.println(tempfile);
    while (SD.exists(tempfile))
    {
      SerialUSB.println(tempfile);
      count++;
      tempfile = DataFolder + "/DATA" + String(count) + ".CSV";
    }
    
  }
  return count;
}

bool CreateNewDatafile()
{
  DataFileName = DataFolder + "/DATA" + String(CountDataFiles()) + ".CSV";
  DataFile = SD.open(DataFileName, FILE_WRITE);

  if(DataFile)
  {
    SerialUSB.println("Created Data File");
    writeInfo("Created Data File", NORMAL);   
    return true;
  }
  else
  {
    return false;
  }
}

void WriteHeaders()
{
  String header;
  Serial.println(HeaderArray_length);
  for (size_t i = 0; i < HeaderArray_length; i++)
  {
    if(i == HeaderArray_length-1)
    {
      header += headers[i];
    }
    else
    {
      header += headers[i] + ",";
    } 
  }

  if(SD_CARD_INITIALIZED)
  {
    if(DataFile)
    {
      SerialUSB.println("test header");
      DataFile.println(header);
    }
  }
}

void LogDelay()
{
  time_now = millis();
  
  if(LOW_USE_MODE)
  {
    while(millis() < time_now + LOG_DELAY_LONG){
        //wait approx. 2 minutes
    }
  }
  else
  {
    while(millis() < time_now + LOG_DELAY_NORMAL){
        //wait approx. 20 seconds
    }
  }
}


bool LogSN01()
{
  // SN01
  if (ping(SN01_ADRESS))
  {
    xSN01 SN01;
    while (true);//TODO - change and use SN01.dataAvailable());
    if ((SN01.getHDOP() < 10.0) & (SN01.getHDOP() > 0.0))
    {
      GPS_FIX = false;
      logdata(log_index++, SN01.getDate());
      logdata(log_index++, SN01.getTime());
      logdata(log_index++, String(SN01.getLatitude(), 5));
      logdata(log_index++, String(SN01.getLongitude(), 5));
      logdata(log_index++, SN01.getAltitude());
      logdata(log_index++, SN01.getHDOP());
      logdata(log_index++, SN01.getSOG());
      logdata(log_index++, SN01.getCOG());
      logdata(log_index++, (long)SN01.getSatelitesConnected());
      return true;
    }
    else
    {
      GPS_FIX = true;
      logdata(log_index++, "");
      logdata(log_index++, "");
      logdata(log_index++, "");
      logdata(log_index++, "");
      logdata(log_index++, "");
      logdata(log_index++, "");
      logdata(log_index++, "");
      logdata(log_index++, "");
      logdata(log_index++, "");
      return false;
    }
  }
  else
  {
    logdata(log_index++, "");
    logdata(log_index++, "");
    logdata(log_index++, "");
    logdata(log_index++, "");
    logdata(log_index++, "");
    logdata(log_index++, "");
    logdata(log_index++, "");
    logdata(log_index++, "");
    logdata(log_index++, "");
    return false;
  }
  
}

bool LogSL01()
{
  if (ping(SL01_ADRESS_1) && ping(SL01_ADRESS_2))
  {
    xSL01 SL01;
    SL01.begin();
    SL01.poll();
    
    logdata(log_index++, SL01.getUVA());
    logdata(log_index++, SL01.getUVB());
    logdata(log_index++, SL01.getUVIndex());
    logdata(log_index++, SL01.getLUX());
    return true;
  }
  else
  {
    logdata(log_index++, "");
    logdata(log_index++, "");
    logdata(log_index++, "");
    logdata(log_index++, "");
    return false;
  }
}

bool LogSW01()
{
  if (ping(SW01_ADRESS) == true)
  {
    xSW01 SW01;
    if (SW01.begin())
    {
      SW01.poll();
      logdata(log_index++, SW01.getTempC());
      logdata(log_index++, SW01.getPressure());
      logdata(log_index++, SW01.getHumidity());
      logdata(log_index++, SW01.getQNE());
      return true;
    }
  }
  else
  {
    logdata(log_index++, "");
    logdata(log_index++, "");
    logdata(log_index++, "");
    logdata(log_index++, "");
    return false;
  }
}

bool LogSG33()
{
  if (ping(SG33_ADRESS))
  {
    xSG33 SG33;
    if(SG33.begin())
    {
      if (SG33.dataAvailable())     //TODO in the library example, theres a 2 second delay to wait for sensor to normalise
      {
        SG33.getAlgorithmResults();
        logdata(log_index++, (uint16_t)SG33.getTVOC());
        logdata(log_index++, (uint16_t)SG33.getCO2());
        return true;
      }
      else
      {
        logdata(log_index++, "");
        logdata(log_index++, "");
        return false;
      }
    }
    else
    {
      logdata(log_index++, "");
      logdata(log_index++, "");
      return false;
    }
  }
  else
  {
    logdata(log_index++, "");
    logdata(log_index++, "");
    return false;
  }
}

bool LogPB04()
{
  if (ping(PB04_ADRESS))
  {
    xPB04 PB04;
    PB04.begin();
    PB04.poll();
    logdata(log_index++, PB04.getCurrent());
    logdata(log_index++, PB04.getVoltage());
    return true;
  }
  else
  {
    logdata(log_index++, "");
    logdata(log_index++, "");
    return false;
  }
}

bool LogSI01()
{
  if (ping(SI01_ADRESS_1) && ping(SI01_ADRESS_2))
  {
    xSI01 SI01;
    SI01.begin();
    SI01.poll();
    
    logdata(log_index++, SI01.getRoll());
    logdata(log_index++, SI01.getPitch());
    logdata(log_index++, SI01.getGForce());
    logdata(log_index++, SI01.getMX());
    logdata(log_index++, SI01.getMY());
    logdata(log_index++, SI01.getMZ());
    logdata(log_index++, SI01.getGX());
    logdata(log_index++, SI01.getGY());
    logdata(log_index++, SI01.getGZ());
    logdata(log_index++, SI01.getAX());
    logdata(log_index++, SI01.getAY());
    logdata(log_index++, SI01.getAZ());
    return true;
  }
  else
  {
    
    logdata(log_index++, "");
    logdata(log_index++, "");
    logdata(log_index++, "");
    logdata(log_index++, "");
    logdata(log_index++, "");
    logdata(log_index++, "");
    logdata(log_index++, "");
    logdata(log_index++, "");
    logdata(log_index++, "");
    logdata(log_index++, "");
    logdata(log_index++, "");
    logdata(log_index++, "");
    return false;
  }
}

bool LogRL0X()
{
  if (RL03.lastRssi())
    {
      //logdata(log_index++, receivedRSSI);        //TODO need to add this line in at some point
      logdata(log_index++, "");
      logdata(log_index++, "");
      //logdata(log_index++, config.RADIO_ID);       //TODO need to add this line in when the other RADIO stuff has been added
      return true;
    }
    else
    {
      logdata(log_index++, "");
      logdata(log_index++, "");
      return false;
    }
}
