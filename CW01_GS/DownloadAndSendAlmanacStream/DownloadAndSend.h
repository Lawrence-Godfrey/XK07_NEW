const float RL03_FREQ {915.0}
// Radio Address
const uint8_t RADIO_ID {0x31};

bool lastPacketSuccesfull;

const char[] SSID {"XinaBox"};
const char[] password {"RapidIoT"};

const char[] UBLOX_URL {"http://online-live1.services.u-blox.com/GetOnlineData.ashx?token=SjneqlMN-UG2zAzl_Egmdw;gnss=gps;datatype=eph,alm,aux,pos;filteronpos;format=aid"};
const char[] UBLOX_URL_BACKUP {"http://online-live2.services.u-blox.com/GetOnlineData.ashx?token=SjneqlMN-UG2zAzl_Egmdw;gnss=gps;datatype=eph,alm,aux,pos;filteronpos;format=aid"};

const uint8_t BUFFER_SIZE {120};