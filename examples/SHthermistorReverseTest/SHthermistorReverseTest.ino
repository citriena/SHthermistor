#include <SHthermistor.h>     // https://github.com/citriena/SHthermistor

//SHthermistor thermistor(  0, 50, 100,  3329, 358.6, 67.57); // M861/1k/A6
//SHthermistor thermistor(  0, 25,  70,  3329,  1002, 173.7); // M861/1k/A6
SHthermistor thermistor(-20, 25,  50, 10081,  1002, 358.6); // M861/1k/A6

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  Serial.print("SH_A = ");
  Serial.println(thermistor.getSH_A(), 15);
  Serial.print("SH_B = ");
  Serial.println(thermistor.getSH_B(), 15);
  Serial.print("SH_C = ");
  Serial.println(thermistor.getSH_C(), 15);
  Serial.println("-------------------------------");
  Serial.print("R = ");
  Serial.println(thermistor.temp2r(10),4);
  Serial.println("-------------------------------");
  delay(1000);
}