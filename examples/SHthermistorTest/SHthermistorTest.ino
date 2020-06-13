/*
circuit
 Vdd---SERIES_RESISTOR---A0---NTC thermistor---GND
*/

#include <SHthermistor.h>

SHthermistor thermistor(0, 25, 50, 27280, 10000, 4160, 10000, 0, NTC_GND);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly://
  Serial.println(thermistor.readTemp(), 1);
  delay(1000);
}