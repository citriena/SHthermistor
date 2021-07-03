#include <SHthermistor.h>     // https://github.com/citriena/SHthermistor

SHthermistor thermistor(0, 25, 50, 27280, 10000, 4160, 10000, A0, NTC_GND);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.print("SH_A = ");
  Serial.println(thermistor.getSH_A(), 15);
  Serial.print("SH_B = ");
  Serial.println(thermistor.getSH_B(), 15);
  Serial.print("SH_C = ");
  Serial.println(thermistor.getSH_C(), 15);
}

void loop() {
}
