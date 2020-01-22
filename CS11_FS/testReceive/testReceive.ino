#include <xCore.h>
#include <xRL0x.h>
#include <xCS11_SDU.h>

#define ADDR_ID 0x11
#define FROM_ID 0x11
#define TO_ID   0x31

#define RL03_FREQ 915.0

void setup()
{
  SerialUSB.begin(115200);
  Wire.begin();

  if (!RL0X.begin()) { // <-- enter radio name here
    SerialUSB.println("Check the connector to RL03");
    while (1) {
      // Flash RED to indicate failure
      
      delay(100);
      
      delay(100);
    }
  } else {
    // CR01 Initialized correctly
    //RL01.setModemConfig(RL01.Bw31_25Cr48Sf512);
    RL0X.setFrequency(RL03_FREQ);
    RL0X.setTxPower(23, false);
    RL0X.setThisAddress(ADDR_ID);
    RL0X.setHeaderFrom(FROM_ID);
    RL0X.setHeaderTo(TO_ID);
  }
}

void loop()
{
  while(RL0X.waitAvailableTimeout(3000))
  {
    uint8_t start_seq[] = "[START]";
    
    uint8_t buf[sizeof(start_seq)];
    uint8_t len = sizeof(buf);

    SerialUSB.println("receiving start sequence");
      
    if (RL0X.recv(buf, &len)) {
      if(equalarrays(start_seq, buf, len))
      {
         uint8_t sendback[1]; 
         while(RL0X.waitAvailableTimeout(3000))
        {
          uint8_t check[1];
          uint8_t len = 1;

          if (RL0X.recv(check, &len)) {
            if(check[0]==0)
            {
              SerialUSB.println("Got 0\nSending 0");
              sendback[0] =0;
            }
            else if(check[0]==1)
            {
              SerialUSB.println("Got 1\nSending 1");
              sendback[0] = 1;
            }
            else
            {
              SerialUSB.println("Neither");
              return;
            }
            
            delay(300);
            RL0X.send(sendback, 1);

          } else {
            SerialUSB.println("[RADIO] Could not receive check bit");
            return;
          }
        }
      }
    }
  }
}

bool equalarrays(uint8_t a[], uint8_t b[], uint8_t n)
{
  for (int i = 0; i < n; i++)
  {
    if (a[i] != b[i])
    {
      return false;
    }
  }
  return true;
}
