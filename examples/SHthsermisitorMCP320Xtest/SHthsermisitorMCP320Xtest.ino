#include <SHthermistorMCP320X.h>

SHthermistorMCP320X thermistor(0, 25, 50, 27280, 10000, 4160, 10000, 1, NTC_GND);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  thermistor.begin(10, 0);
}
void loop() {
  // put your main code here, to run repeatedly://
  Serial.println(thermistor.readTemp(), 1);
  Serial.println(thermistor.readR());
  Serial.println();
  delay(1000);
}
