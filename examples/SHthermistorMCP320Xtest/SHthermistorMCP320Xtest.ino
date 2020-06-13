#include "SHthermistorMCP320X.h"

SHthermistorMCP320X thermistor(0, 25, 50, 27280, 10000, 4160, 10000, 0, NTC_GND);   // adcPin means analog input channel of MCP320X in SHthermistorMCP320X.
//SHthermistorMCP320X thermistor(0, 25, 50, 27280, 10000, 4160, 10000, 0, NTC_GND, -1, 0, ADC_12BIT_VALUE);   // adcPin means analog input channel of MCP320X in SHthermistorMCP320X.


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  thermistor.begin(10);  // set CS (chip select) as argument of begin()
}


void loop() {
  // put your main code here, to run repeatedly://
  Serial.println(thermistor.readTemp(), 2);
  Serial.println();
  delay(1000);
}