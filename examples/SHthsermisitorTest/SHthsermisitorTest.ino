#include <SHthermistor.h>

SHthermistor thermistor(0, 25, 50, 27280, 10000, 4160, 1, 10000, NTC_GND, 0, 9);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}
void loop() {
  // put your main code here, to run repeatedly://
  Serial.println(thermistor.readTemp(), 1);
  delay(1000);
}}