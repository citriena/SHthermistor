#ifndef SHthermistor_h
#define SHthermistor_h
#include <Arduino.h> 

#define READ_TIMES 11
#define MEDIAN_ORDER (int)(READ_TIMES / 2)

#define ADC_10BIT_VALUE  1024 // 0x00400
#define ADC_12BIT_VALUE  4096 // 0x01000
#define ADC_14BIT_VALUE 16384 // 0x04000
#define ADC_16BIT_VALUE 65536 // 0x10000

#define DEFAULT_EXCITE_VALUE ADC_10BIT_VALUE

typedef enum {
  NTC_EXCITE,
  NTC_GND,
} NTC_CONNECT_t;


class SHthermistor { 
public:
  SHthermistor(float SH_T1, float SH_T2, float SH_T3, // low, mid, and high temperature (Celcius) including actual measure condition
               float SH_R1, float SH_R2, float SH_R3, // thermistor resistance (ohm) at SH_T1, SH_T2, SH_T3
               float divR,                  // resistance value (ohm) of series divider resistor
               uint8_t adcPin,              // analog pin connected to thermistor and series resistor
               NTC_CONNECT_t ntcConnect,    // connection of thermistor and series resistor
               int8_t excitePin,            // Voltage supply pin. When excitePin is set the voltage will be supplied only during measurement. Default value is -1 (do not control).
               float offsetT,               // offset value added to calculated temperature
               uint32_t exciteValue         // ADC read value of excitePin (in case of Arduino excitePin = VREF( = Vdd))
  );



  SHthermistor(float SH_T1, float SH_T2, float SH_T3, float SH_R1, float SH_R2, float SH_R3, float divR, uint8_t adcPin, NTC_CONNECT_t ntcConnect, int8_t excitePin, float offsetT);
  SHthermistor(float SH_T1, float SH_T2, float SH_T3, float SH_R1, float SH_R2, float SH_R3, float divR, uint8_t adcPin, NTC_CONNECT_t ntcConnect, int8_t excitePin);
  SHthermistor(float SH_T1, float SH_T2, float SH_T3, float SH_R1, float SH_R2, float SH_R3, float divR, uint8_t adcPin, NTC_CONNECT_t ntcConnect);

  SHthermistor(float shA, float shB, float shC, float divR, uint8_t adcPin, NTC_CONNECT_t ntcConnect, int8_t excitePin, float offsetT, uint32_t exciteValue);

  void setSHcoef(float shA, float shB, float shC);
  void setSHcoef(float SH_T1, float SH_T2, float SH_T3, float SH_R1, float SH_R2, float SH_R3);
  float readR();
  virtual uint16_t readAdc(uint8_t adcChannel);
  float r2temp(float r);
  float readTemp();
  void setDivR(float divR);
  void setOffsetTemp(float offsetT);

protected:

  float SH_A;
  float SH_B;
  float SH_C;
  float _DIV_R;
  uint8_t _ADC_CHANNEL;
  float _OFFSET_TEMP;
  int8_t _EXCITE_PIN;
  NTC_CONNECT_t _NTC_CONNECT;
  int32_t _EXCITE_VALUE;
  uint32_t _ADC_HL;

  void setExciteValue(uint32_t exciteValue);
  void sort(uint16_t a[], uint8_t size);

private:

};
#endif
