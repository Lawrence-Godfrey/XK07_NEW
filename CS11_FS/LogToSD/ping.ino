/***
  ping a entered I2C address on the BUS
***/
bool ping(uint8_t _address)
{
  // Set flag status
  bool status = false;
  // Check the flag status to check if OD01 is connected and ping was succesful
  for (uint8_t i = 0; i < 10; i++) {
    Wire.beginTransmission(_address);
    if (Wire.endTransmission () == 0) { // Device is connected and ping successful
      status = true; // set flag
      break; // exit loop
    } else if (i < 8) { // Device not found cannot ping device address
      status = false; // set flag
      break; // exit loop
    }
    delay(10);
  }
  return status;
}
