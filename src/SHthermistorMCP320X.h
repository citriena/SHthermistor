#ifndef SHthermistorMCP320X_h
#define SHthermistorMCP320X_h
#include <SHthermistor.h>

#define DATAOUT   11 //MOSI
#define DATAIN    12 //MISO 
#define SPICLOCK  13 //Clock 


#undef DEFAULT_EXCITE_VALUE
#define DEFAULT_EXCITE_VALUE ADC_12BIT_VALUE     // 1024 (2^10) 

class SHthermistorMCP320X : public SHthermistor {
public:
  using SHthermistor::SHthermistor;

  void begin(int8_t SELPIN, int8_t channel);
  virtual uint16_t readAdc();

protected:

private:
  int8_t _CHANNEL = 0;
  int8_t _SELPIN;
};
#endif
