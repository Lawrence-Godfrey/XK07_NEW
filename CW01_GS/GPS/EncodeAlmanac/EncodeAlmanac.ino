#include <rBase64.h>

void setup() {
  Serial.begin(115200);
}

void loop() {

  String payload = "�b0                   )���I ��b1h    $K? P"
" )�C�! 觿��81X�� O�� <�X �L+�g),���� ��w"
"}81 �  �7�� )� ��� ��I�X7��b1h    $K? P"
" )�C�! 觿ڨ�810 ��  ��� �0 �C0ҽ� "
"���3��"
"|81 ֎  0�!;  #X�� ����S 0 8��b1h    $K? P"
" )�C�! 觿��71 �� 9��K� ]0�k: a� U �� �"
" B71 �� �  ��� �";

//  std::vector<uint8_t> myVector(0,79);
//  uint8_t *p = &myVector[0];


//  uint8_t* p = reinterpret_cast<uint8_t*>(&payload[0]);
  
//  size_t alm_size = payload.length();
//  uint8_t almanac[alm_size + 1];
//  strcpy(almanac, payload.c_str());
    

  
  
  // Serial.println(payload.length());
  // if (rbase64.encode(payload) == RBASE64_STATUS_OK) {
  //   Serial.println("\nConverted the String to Base64 : ");
  //   Serial.println(rbase64.result());
  // }

  // if (rbase64.decode(rbase64.result()) == RBASE64_STATUS_OK ) {
  //   Serial.println("\nConverted the String from Base64 : ");
  //   Serial.println(rbase64.result());
  // }
  delay(10000);
}
