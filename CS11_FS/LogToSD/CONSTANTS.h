vector <vector<String>>  headers{    //these don't actually have to be vectors (BUT vectors do have out-of-bounds checks built-in)
  {"Runtime",
   "Date",
   "Time"},

  {"Latitude",
   "Longitude",
   "GPS Altitude",
   "HDOP",
   "Speed",
   "Bearing",
   "Satelites"},

  {"UVA",
   "UVB",
   "UV Index",
   "Ambient Light SL01"},

  {"Temperature",
   "Pressure",
   "Humidity",
   "Altitude"},

  {"eC02",
   "TVOC"},

  {"Current",
   "Voltage"},

  {"Roll",
   "Pitch",
   "G-Force",
   "Magnetometer X-Axis",
   "Magnetometer Y-Axis",
   "Magnetometer Z-Axis",
   "Gyroscope X-Axis",
   "Gyroscope Y-Axis",
   "Gyroscope Z-Axis",
   "Accelerometer X-Axis",
   "Accelerometer Y-Axis",
   "Accelerometer Z-Axis"},

  {"Radio ID",
   "Received RSSI"}
}



// #define ARRAYSIZE 37

//i2c Adresses
#define SL01_ADRESS_1 0x10
#define SL01_ADRESS_2 0x29
#define SW01_ADRESS 0x76
#define SG33_ADRESS 0x5A
#define PB04_ADRESS 0x36
#define SI01_ADRESS_1 0x1C
#define SI01_ADRESS_2 0x6A

bool LOW_USE_MODE {false};

bool SD_CARD_INITIALIZED {false};

File DataFile;
File InfoFile;

String filename;
String filename_info {"infoFile.txt"};
String DataFolder {"/XK07Data"};

int LOG_DELAY_LONG {120000};
int LOG_DELAY_NORMAL {20000};
unsigned long time_now {0};

#define IMPORTANT 1
#define NORMAL 0
