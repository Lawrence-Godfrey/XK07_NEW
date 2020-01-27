#include <SD_LOG.h>

SD_LOG::SD_LOG()
{

}

void SD_LOG::WriteInfo(char info[])
{
  infoFile = SD.open("infoFile.txt");
  if (SD_CARD_INITIALIZED) {
    if (infoFile) {
      infoFile.println(info);
    }
  }
  infoFile.close();
}

void SD_LOG::logdata(float data) {
  // Log To SD Card
  if (SD_CARD_INITIALIZED) {
    if (DataFile) {
      DataFile.print(data);
      DataFile.print(",");
    }
  }
}

void SD_LOG::logdata(int index, int data) {
  // Log To SD Card
  if (SD_CARD_INITIALIZED) {
    if (DataFile) {
      DataFile.print(data);
      DataFile.print(",");
    }
  }
}

void SD_LOG::logdata(int index, long data) {
  // Log To SD Card
  if (SD_CARD_INITIALIZED) {
    if (DataFile) {
      DataFile.print(data);
      DataFile.print(",");
    }
  }
}

void SD_LOG::logdata(int index, char data[]) {
  // Log To SD Card
  if (SD_CARD_INITIALIZED) {
    if (DataFile) {
      DataFile.print(data);
      DataFile.print(",");
    }
  }
}

void SD_LOG::logdata(int index, uint32_t data) {
  // Log To SD Card
  if (SD_CARD_INITIALIZED) {
    if (DataFile) {
      DataFile.print(data);
      DataFile.print(",");
    }
  }
}

void SD_LOG::logdata(int index, uint16_t data) {
  // Log To SD Card
  if (SD_CARD_INITIALIZED) {
    if (DataFile) {
      DataFile.print(data);
      DataFile.print(",");
    }
  }
}

void SD_LOG::logdata(int index, String data) {
  // Log To SD Card
  if (SD_CARD_INITIALIZED) {
    if (DataFile) {
      DataFile.print(data);
      DataFile.print(",");
    }
  }
}

uint16_t SD_LOG::CountDataFiles()
{
  uint16_t count = 0;
  if (SD_CARD_INITIALIZED) {
    if (SD.begin(3)) {
      
      String tempfile
    
      do {
        tempfile = "DATA" + String(count++) + ".csv";
        Watchdog.reset();
      } while (SD.exists(tempfile));
    }
  }
  return count;
}

