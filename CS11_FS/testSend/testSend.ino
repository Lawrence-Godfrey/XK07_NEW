#include <xRL0x.h>
#define RL03_FREQ 915.0

#define ADDR_ID 0x31
#define FROM_ID 0x31
#define TO_ID   0x11

void setup()
{
  Serial.begin(115200);
  Wire.begin();

  if (!RL0X.begin())
  { // <-- enter radio name here
    Serial.println("Check the connector to CR01");
    while (1)
    {
      // Flash RED to indicate failure
      delay(100);
    }
  }
  else
  {
    // RL0X Initialized correctly
    //RL0X.setModemConfig(RL01.Bw31_25Cr48Sf512);
    RL0X.setFrequency(RL03_FREQ);
    RL0X.setTxPower(23, false);
    RL0X.setThisAddress(ADDR_ID);
    RL0X.setHeaderFrom(FROM_ID);
    RL0X.setHeaderTo(TO_ID); 
  }
}

void loop()
{
  String payload = "This is a test"
                   "Definitely a test"
                   "nothing more than a test"
                   "just testing if everything works and now this is a long sentence that i'm testing and its being tested and its long"
                   "This is a test 2"
                   "Definitely a test"
                   "nothing more than a test"
                   "just testing if everything works and now this is a long sentence that i'm testing and its being tested and its long"
                   "This is a test 3"
                   "Definitely a test"
                   "nothing more than a test"
                   "just testing if everything works and now this is a long sentence that i'm testing and its being tested and its long"
                   "This is a test 4"
                   "Definitely a test"
                   "nothing more than a test"
                   "just testing if everything works and now this is a long sentence that i'm testing and its being tested and its long";

  int alm_size = payload.length();

  while(true)
  {
    char almanac[alm_size + 1];
    strcpy(almanac, payload.c_str());    

    uint8_t start_seq[] = "[START]";
    delay(100);
    RL0X.send(start_seq, sizeof(start_seq));
    
    delay(300);

    uint8_t sendback[1];
    uint8_t firstSend[1] {1}; 
    RL0X.send(firstSend,1);
    
    while(RL0X.waitAvailableTimeout(3000))
    {
      uint8_t check[1];
      uint8_t len = 1;

      if (RL0X.recv(check, &len)) {
        
        if(check[0]==0)
        {
          Serial.println("Got 0\nSending 0");
          sendback[0] = 1;
        }
        else if(check[0]==1)
        {
          Serial.println("Got 1\nSending 1");
          sendback[0] =0 ;
        }
        else
        {
          Serial.println("Neither");
          return;
        }
        
        delay(300);
        RL0X.send(sendback, 1);

      } else {
        Serial.println("[RADIO] Could not receive check bit");
        return;
      }
    }



  }
}
