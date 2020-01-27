void logdata(float data) {
  // Log To SD Card
  if (SD_CARD_INITIALIZED) {
    if (DataFile) {
      DataFile.print(data);
      DataFile.print(",");
    }
  }
}

void logdata(int data) {
  // Log To SD Card
  if (SD_CARD_INITIALIZED) {
    if (DataFile) {
      DataFile.print(data);
      DataFile.print(",");
    }
  }
}

void logdata(long data) {
  // Log To SD Card
  if (SD_CARD_INITIALIZED) {
    if (DataFile) {
      DataFile.print(data);
      DataFile.print(",");
    }
  }
}

void logdata(char data[]) {
  // Log To SD Card
  if (SD_CARD_INITIALIZED) {
    if (DataFile) {
      DataFile.print(data);
      DataFile.print(",");
    }
  }
}

void logdata(uint32_t data) {
  // Log To SD Card
  if (SD_CARD_INITIALIZED) {
    if (DataFile) {
      DataFile.print(data);
      DataFile.print(",");
    }
  }
}

void logdata(uint16_t data) {
  // Log To SD Card
  if (SD_CARD_INITIALIZED) {
    if (DataFile) {
      DataFile.print(data);
      DataFile.print(",");
    }
  }
}

void logdata(String data) {
  // Log To SD Card
  if (SD_CARD_INITIALIZED) {
    if (DataFile) {
      DataFile.print(data);
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
  filename = DataFolder + "/DATA" + String(CountDataFiles()) + ".CSV";
  DataFile = SD.open(filename, FILE_WRITE);

  if(DataFile)
  {
    SerialUSB.println("Created Data File");
    WriteInfo_SD("Created Data File", NORMAL);   
    return true;
  }
  else
  {
    return false;
  }
}

bool LogSN01()
{
  logdata("");
  logdata("");
  logdata("");
  logdata("");
  logdata("");
  logdata("");
  logdata("");
  logdata("");
  logdata("");
  logdata("");
  return true;
}

bool LogSL01()
{
  if ((ping(SL01_ADRESS_1) && ping(SL01_ADRESS_2)) == true)
  {
    xSL01 SL01;
    SL01.begin();
    SL01.poll();
    
    logdata(SL01.getUVA());
    logdata(SL01.getUVB());
    logdata(SL01.getUVIndex());
    logdata(SL01.getLUX());
    return true;
  }
  else
  {
    logdata("");
    logdata("");
    logdata("");
    logdata("");
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
      logdata(SW01.getTempC());
      logdata(SW01.getPressure());
      logdata(SW01.getHumidity());
      logdata(SW01.getQNE());
      return true;
    }
  }
  else
  {
    logdata("");
    logdata("");
    logdata("");
    logdata("");
    return false;
  }
}

bool LogSG33()
{
  if (ping(SG33_ADRESS) == true)
  {
    xSG33 SG33;
    if(SG33.begin())
    {
      if (SG33.dataAvailable())     //TODO in the library example, theres a 2 second delay to wait for sensor to normalise
      {
        SG33.getAlgorithmResults();
        logdata((uint16_t)SG33.getTVOC());
        logdata((uint16_t)SG33.getCO2());
        return true;
      }
      else
      {
        logdata("");
        logdata("");
        return false;
      }
    }
    else
    {
      logdata("");
      logdata("");
      return false;
    }
  }
  else
  {
    logdata("");
    logdata("");
    return false;
  }
}

bool LogPB04()
{
  if (ping(PB04_ADRESS) == true)
  {
    xPB04 PB04;
    PB04.begin();
    PB04.poll();
    logdata(PB04.getCurrent());
    logdata(PB04.getVoltage());
    return true;
  }
  else
  {
    logdata("");
    logdata("");
    return false;
  }
}

bool LogSI01()
{
  if ((ping(SI01_ADRESS_1) && ping(SI01_ADRESS_2)) == true)
  {
    xSI01 SI01;
    SI01.begin();
    SI01.poll();
    
    logdata(SI01.getRoll());
    logdata(SI01.getPitch());
    logdata(SI01.getGForce());
    logdata(SI01.getMX());
    logdata(SI01.getMY());
    logdata(SI01.getMZ());
    logdata(SI01.getGX());
    logdata(SI01.getGY());
    logdata(SI01.getGZ());
    logdata(SI01.getAX());
    logdata(SI01.getAY());
    logdata(SI01.getAZ());
    return true;
  }
  else
  {
    
    logdata("");
    logdata("");
    logdata("");
    logdata("");
    logdata("");
    logdata("");
    logdata("");
    logdata("");
    logdata("");
    logdata("");
    logdata("");
    logdata("");
    return false;
  }
}

bool LogRL0X()
{
  if (RL03.lastRssi())
    {
      //logdata(receivedRSSI);        //TODO need to add this line in at some point
      logdata("");
      logdata("");
      //logdata(config.RADIO_ID);       //TODO need to add this line in when the other RADIO stuff has been added
      return true;
    }
    else
    {
      logdata("");
      logdata("");
      return false;
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

void WriteHeaders()
{
  String header;
  for (size_t i = 0; i < headers.size(); i++)
  {
    for (size_t j = 0; j < headers.at(i).size(); j++)
    {
      if(i == headers.size()-1 && j == headers.at(i).size-1)
      {
        header += headers.at(i).at(j);
      }
      else
      {
        header += headers.at(i).at(j) + ",";
      }
      
    }
    
  }
}

