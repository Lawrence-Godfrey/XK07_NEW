#ifndef DataLogging_h
#define DataLogging_h

const char header[] {"Runtime,"
"Date,"
"Time,"
"Latitude,"
"Longitude,"
"GPS Altitude,"
"HDOP,"
"Speed,"
"Bearing,"
"Satelites,"
"UVA,"
"UVB,"
"UV Index,"
"Ambient Light SL01,"
"Temperature,"
"Pressure,"
"Humidity,"
"Altitude,"
"eC02,"
"TVOC,"
"Current,"
"Voltage,"
"Roll,"
"Pitch,"
"G-Force,"
"Magnetometer X-Axis,"
"Magnetometer Y-Axis,"
"Magnetometer Z-Axis,"
"Gyroscope X-Axis,"
"Gyroscope Y-Axis,"
"Gyroscope Z-Axis,"
"Accelerometer X-Axis,"
"Accelerometer Y-Axis,"
"Accelerometer Z-Axis,"
"Radio ID,"
"Received RSSI"};

#define ARRAYSIZE 37

#define SL01_ADRESS_1 0x10
#define SL01_ADRESS_2 0x29
#define SW01_ADRESS 0x76
#define SG33_ADRESS 0x5A
#define PB04_ADRESS 0x36
#define SI01_ADRESS_1 0x1C
#define SI01_ADRESS_2 0x6A

bool SD_CARD_INITIALIZED {false};

File DataFile;
File InfoFile;

String filename;

class DataLogging
{
  public:
    void SD_LOG::WriteInfo(char info[]);

    void SD_LOG::logdata(float data);

    void SD_LOG::logdata(int index, int data);

    void SD_LOG::logdata(int index, long data);

    void SD_LOG::logdata(int index, char data[]);

    void SD_LOG::logdata(int index, uint32_t data);

    void SD_LOG::logdata(int index, uint16_t data);

    void SD_LOG::logdata(int index, String data);

    uint8_t SD_LOG::CountDataFiles();


}


#endif
