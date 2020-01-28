const String headers[] {             // TODO - could be improved by using seperate arrays for each sensor, or using vectors
  "Runtime",
  "Date",
  "Time",
  "Latitude",
  "Longitude",
  "GPS Altitude",
  "HDOP",
  "Speed",
  "Bearing",
  "Satelites",
  "UVA",
  "UVB",
  "UV Index",
  "Ambient Light SL01",
  "Temperature",
  "Pressure",
  "Humidity",
  "Altitude",
  "eC02",
  "TVOC",
  "Current",
  "Voltage",
  "Roll",
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
  "Accelerometer Z-Axis",
  "Radio ID",
  "Received RSSI"
};

const String units[] {
  "",
  "",
  "",
  "",
  "",
  "m",
  "",
  "kph",
  "deg",
  "",
  "uW/cm^2",
  "uW/cm^2",
  "",
  "Lx",
  "*C",
  "Pa",
  "RH%",
  "m",
  "ppm",
  "ppb",
  "mA",
  "V",
  "deg",
  "deg",
  "g",
  "gauss",
  "gauss",
  "gauss",
  "deg/s",
  "deg/s",
  "deg/s",
  "g",
  "g",
  "g",
  "",
  "dB",
};

const unsigned int HeaderArray_length {sizeof(headers)/sizeof(headers[0])};


//i2c Adresses
// TODO - ADD Alternate adresse, add RL0x adresses, OD01? 
#define SN01_ADRESS 0x42

#define SL01_ADRESS_1 0x10
#define SL01_ADRESS_2 0x29

#define SW01_ADRESS 0x76
#define SW01_ADRESS_ALT 0x77

#define SG33_ADRESS 0x5A
#define SG33_ADRESS_ALT 0x5B

#define PB04_ADRESS 0x36

#define SI01_ADRESS_1 0x1C
#define SI01_ADRESS_1_ALT 0x1E
#define SI01_ADRESS_2 0x6A
#define SI01_ADRESS_2_ALT 0x6B

#define OD01_ADRESS 0x3C

bool LOW_USE_MODE {false};

bool SD_CARD_INITIALIZED {false};

File DataFile;
File InfoFile;

String DataFileName;
const String InfoFileName {"XK07Info.txt"};
const String DataFolder {"/XK07Data"};

unsigned int log_index;

const unsigned int LOG_DELAY_LONG {120000};
const unsigned int LOG_DELAY_NORMAL {20000};
const unsigned int LOG_DELAY_SHORT {5000};
unsigned long time_now {0};

#define IMPORTANT 1
#define NORMAL 0

bool GPS_FIX;
