#ifndef SHthermistor_h
#define SHthermistor_h

#if defined(ARDUINO) && ARDUINO >= 100
#include <Arduino.h> 
#else
#include <WProgram.h> 
#endif


#define READ_TIMES 11
#define MEDIAN_ORDER (int)(READ_TIMES / 2)


#define ADC_10BIT_VALUE  1024 // 0x00400
#define ADC_12BIT_VALUE  4096 // 0x01000
#define ADC_14BIT_VALUE 16384 // 0x04000
#define ADC_16BIT_VALUE 65536 // 0x10000


#define DEFAULT_EXCITE_VALUE ADC_10BIT_VALUE     // 1024 (2^10) 

typedef enum {
  NTC_EXCITE,
  NTC_GND,
} NTC_CONNECT_t;


class SHthermistor { 
public:
  SHthermistor(float SH_T1, float SH_T2, float SH_T3, // 
               float SH_R1, float SH_R2, float SH_R3, // 
               float divR,                  // 
               int8_t adcPin,               // 
               NTC_CONNECT_t ntcConnect,    // 
               int8_t vinPin,               // 
               float offsetT,               // 
               uint32_t exciteValue         // 
               );

  SHthermistor(float SH_T1, float SH_T2, float SH_T3, float SH_R1, float SH_R2, float SH_R3, float divR, int8_t adcPin, NTC_CONNECT_t ntcConnect, int8_t vinPin, float offsetT);

  SHthermistor(float SH_T1, float SH_T2, float SH_T3, float SH_R1, float SH_R2, float SH_R3, float divR, int8_t adcPin, NTC_CONNECT_t ntcConnect, int8_t vinPin);

  SHthermistor(float SH_T1, float SH_T2, float SH_T3, float SH_R1, float SH_R2, float SH_R3, float divR, int8_t adcPin, NTC_CONNECT_t ntcConnect);


  float readR();
  virtual uint16_t readAdc();
  float r2temp(float r);
  float readTemp();
  void setDivR(float divR);
  void setOffsetTemp(float offsetT);

protected:

  double SH_A;
  double SH_B;
  double SH_C;
  int8_t _ADC_PIN;
  float _DIV_R;
  float _OFFSET_TEMP;
  int8_t _EXCITE_PIN;
  int32_t _EXCITE_VALUE = ADC_10BIT_VALUE;
  NTC_CONNECT_t _NTC_CONNECT;
  uint32_t _ADC_HL;

  void setExciteValue(uint32_t exciteValue);
  void sort(uint16_t a[], uint8_t size);

private:

};
#endif
