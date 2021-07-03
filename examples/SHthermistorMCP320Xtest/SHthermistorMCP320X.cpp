// reference:
// https://playground.arduino.cc/Code/MCP3208/

#include "SHthermistorMCP320X.h"

void SHthermistorMCP320X::begin(int8_t SELPIN) {

 //set pin modes 
  _SELPIN = SELPIN;
  pinMode(_SELPIN, OUTPUT);
  pinMode(DATAOUT, OUTPUT);
  pinMode(DATAIN, INPUT);
  pinMode(SPICLOCK, OUTPUT); 
 //disable device to start with
  digitalWrite(_SELPIN, HIGH);
  digitalWrite(DATAOUT, LOW);
  digitalWrite(SPICLOCK, LOW);
  if (_EXCITE_VALUE == DEFAULT_EXCITE_VALUE) {
    setExciteValue(ADC_12BIT_VALUE);
  }
}


uint16_t SHthermistorMCP320X::readAdc(int16_t adcChannel) {

  uint16_t adcvalue = 0;
  uint8_t commandbits = B11000000; //command bits - start, mode, chn (3), dont care (3)

  //allow channel selection
  commandbits |= ((adcChannel)<<3);

  digitalWrite(_SELPIN, LOW);         //Select adc
  // setup bits to be written
  for (int i = 7; i >= 3; i--){
    digitalWrite(DATAOUT, commandbits&1<<i);
    //cycle clock
    digitalWrite(SPICLOCK, HIGH);
    digitalWrite(SPICLOCK, LOW);
  }

  digitalWrite(SPICLOCK, HIGH);    //ignores 2 null bits
  digitalWrite(SPICLOCK, LOW);
  digitalWrite(SPICLOCK, HIGH);
  digitalWrite(SPICLOCK, LOW);

  //read bits from adc
  for (int i = 11; i >= 0; i--){
    adcvalue += digitalRead(DATAIN)<<i;
    //cycle clock
    digitalWrite(SPICLOCK, HIGH);
    digitalWrite(SPICLOCK, LOW);
  }
  digitalWrite(_SELPIN, HIGH); //turn off device
  return adcvalue;
}
