
// writes info to infofile on SD Card. If mode is set to true, it will write to SD Card even if LOW_USE_MODE is active.
void writeInfo(char info[], bool mode)
{
  SerialUSB.println("writeInfo");
  if(mode || !LOW_USE_MODE)
  { 
    SerialUSB.println("making info file");
    InfoFile = SD.open(InfoFileName, FILE_WRITE);
    if (SD_CARD_INITIALIZED) 
    {
      if (InfoFile) 
      {
        InfoFile.println(info);
      }
    }
    InfoFile.close();
  }
}
