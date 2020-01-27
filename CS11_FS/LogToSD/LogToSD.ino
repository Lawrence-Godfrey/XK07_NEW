//XINABOX
#include <xCore.h>
#include <xSW01.h>
#include <xSL01.h>
#include <xSI01.h>
#include <xSN01.h>
#include <xPB04.h>
#include <xRL0x.h>
#include <xSG33.h>
#include <xCS11_SDU.h>

//SD CARD
#include <SPI.h>
#include <SD.h>

#include "CONSTANTS.h"

xRL0X RL03;

void setup()
{
  SerialUSB.begin(115200);
  delay(2000);
  
  Wire.begin();
  
  SerialUSB.println("Starting...");
  
  delay(100);
  
  if (!SD.begin(3)) {
    SerialUSB.println("Card failed, or not present");
    SD_CARD_INITIALIZED = false;
  }
  else
  {
    if(!SD.exists(DataFolder))
    {
      SerialUSB.println("Making Log Folder");
      WriteInfo_SD("[SD CARD] Making Log Folder", NORMAL);
      
      if(SD.mkdir(DataFolder))
      {
        SerialUSB.println("Folder Created");
        WriteInfo_SD("[SD CARD] Folder Created", NORMAL);    
      }
      else
      {
        SerialUSB.println("Could not create Folder");
        WriteInfo_SD("[SD CARD] Could not create Folder", NORMAL);   
      }
    }

    SD_CARD_INITIALIZED = true;
    SerialUSB.println("SD Card initialized.");
    WriteInfo_SD("[SD CARD] SD Card Initialized", NORMAL);

    CreateNewDatafile();
    WriteHeaders();
    DataFile.close();
  }
  
}

void loop()
{
  if(SD_CARD_INITIALIZED){
    DataFile = SD.open(filename, FILE_WRITE);
    SerialUSB.println("Logging Data");
    WriteInfo_SD("[SD CARD] Logging Data", NORMAL); 
    
    //Log Sensor data 
    LogSN01();
    LogSL01();
    LogSW01();
    LogSG33();
    LogPB04();
    LogSI01();
    LogRL0X();

    DataFile.println();
    SerialUSB.println("File Closed");
    WriteInfo_SD("[SD CARD] Datafile Closed", NORMAL); 

    DataFile.close();
  }

  LogDelay();
}

  
