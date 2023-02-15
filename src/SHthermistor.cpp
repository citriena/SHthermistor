#include <SHthermistor.h>

// STEINHART & HART EQUATION: 1/T = a + b(lnR) + c(lnR)^3
// Solve three simultaneous equations to obtain coefficients a,b,c:
// set thermistor resistance SH_R1, SH_R2, SH_R3 (ohm) at SH_T1, SH_T2, SH_T3 (Celcius)
// John M. Zurbuchen. Precision thermistor thermometry. Measurement Science Conference Tutorial: Thermometry-Fundamentals and Practice, 2000.
// http://www.nktherm.com/tec/linearize.html  Steinhart and Hart 式によるサーミスタ抵抗値の温度変換


SHthermistor::SHthermistor(float SH_T1, float SH_T2, float SH_T3, float SH_R1, float SH_R2, float SH_R3, float divR, int16_t adcPin, NTC_CONNECT_t ntcConnect, int8_t excitePin, float offsetT, uint32_t exciteValue) :
  _DIV_R(divR),
  _ADC_CHANNEL(adcPin),
  _OFFSET_TEMP(offsetT),
  _EXCITE_PIN(excitePin),
  _NTC_CONNECT(ntcConnect),
  _EXCITE_VALUE(exciteValue)
{
  setSHcoef(SH_T1, SH_T2, SH_T3, SH_R1, SH_R2, SH_R3);
  setExciteValue(exciteValue);
}


SHthermistor::SHthermistor(float SH_T1, float SH_T2, float SH_T3, float SH_R1, float SH_R2, float SH_R3, float divR, int16_t adcPin, NTC_CONNECT_t ntcConnect, int8_t excitePin, float offsetT) :
  _DIV_R(divR),
  _ADC_CHANNEL(adcPin),
  _OFFSET_TEMP(offsetT),
  _EXCITE_PIN(excitePin),
  _NTC_CONNECT(ntcConnect),
  _EXCITE_VALUE(DEFAULT_EXCITE_VALUE)
{
  setSHcoef(SH_T1, SH_T2, SH_T3, SH_R1, SH_R2, SH_R3);
  setExciteValue(DEFAULT_EXCITE_VALUE);
}


SHthermistor::SHthermistor(float SH_T1, float SH_T2, float SH_T3, float SH_R1, float SH_R2, float SH_R3, float divR, int16_t adcPin, NTC_CONNECT_t ntcConnect, int8_t excitePin) :
  _DIV_R(divR),
  _ADC_CHANNEL(adcPin),
  _OFFSET_TEMP(0),
  _EXCITE_PIN(excitePin),
  _NTC_CONNECT(ntcConnect),
  _EXCITE_VALUE(DEFAULT_EXCITE_VALUE)
{
  setSHcoef(SH_T1, SH_T2, SH_T3, SH_R1, SH_R2, SH_R3);
  setExciteValue(DEFAULT_EXCITE_VALUE);
}


SHthermistor::SHthermistor(float SH_T1, float SH_T2, float SH_T3, float SH_R1, float SH_R2, float SH_R3, float divR, int16_t adcPin, NTC_CONNECT_t ntcConnect) :
  _DIV_R(divR),
  _ADC_CHANNEL(adcPin),
  _OFFSET_TEMP(0),
  _EXCITE_PIN(-1),
  _NTC_CONNECT(ntcConnect),
  _EXCITE_VALUE(DEFAULT_EXCITE_VALUE)
{
  setSHcoef(SH_T1, SH_T2, SH_T3, SH_R1, SH_R2, SH_R3);
  setExciteValue(DEFAULT_EXCITE_VALUE);
}


SHthermistor::SHthermistor(float SH_T1, float SH_T2, float SH_T3, float SH_R1, float SH_R2, float SH_R3) {
  setSHcoef(SH_T1, SH_T2, SH_T3, SH_R1, SH_R2, SH_R3);
}


SHthermistor::SHthermistor(float shA, float shB, float shC, float divR, int16_t adcPin, NTC_CONNECT_t ntcConnect, int8_t excitePin, float offsetT, uint32_t exciteValue) :
  SH_A(shA),
  SH_B(shB),
  SH_C(shC),
  _DIV_R(divR),
  _ADC_CHANNEL(adcPin),
  _OFFSET_TEMP(offsetT),
  _EXCITE_PIN(excitePin),
  _NTC_CONNECT(ntcConnect),
  _EXCITE_VALUE(exciteValue)
{
  setExciteValue(exciteValue);
}


SHthermistor::SHthermistor(float shA, float shB, float shC) :
  SH_A(shA),
  SH_B(shB),
  SH_C(shC)
{
  
}


void SHthermistor::setSHcoef(float shA, float shB, float shC) {
  SH_A = shA;
  SH_B = shB;
  SH_C = shC;
}


void SHthermistor::setSHcoef(float SH_T1, float SH_T2, float SH_T3, float SH_R1, float SH_R2, float SH_R3) {
  SH_T1 += 273.15;
  SH_T2 += 273.15;
  SH_T3 += 273.15;
  float SH_X1 = log(SH_R1);
  float SH_X2 = log(SH_R2);
  float SH_X3 = log(SH_R3);

  float SH_S = (SH_X1 - SH_X2);
  float SH_U = (SH_X1 - SH_X3);
  float SH_V = (1 / SH_T1 - 1 / SH_T2);
  float SH_W = (1 / SH_T1 - 1 / SH_T3);

  SH_C = (SH_V - SH_S * SH_W / SH_U) / ((pow(SH_X1, 3) - pow(SH_X2, 3)) - SH_S * ( pow(SH_X1, 3) - pow(SH_X3, 3)) / SH_U);  // Coefficient c
  SH_B = (SH_V - SH_C * (pow(SH_X1, 3) - pow(SH_X2, 3))) / SH_S;                                                            // Coefficient b
  SH_A = 1 / SH_T1 - SH_C * pow(SH_X1, 3) - SH_B * SH_X1;                                                                   // Coefficient a
}


float SHthermistor::readR() {
  uint16_t Ain = 0;             // alalogRead() value
  float r;                      // resistance of the thermistor
  uint16_t iAin[READ_TIMES];
  uint8_t i;

  if (_EXCITE_PIN >= 0) {
    pinMode(_EXCITE_PIN, OUTPUT);
    digitalWrite(_EXCITE_PIN, HIGH);      // supply voltage only during measurement to avoid self-heating effect
  }
//  if _(ADC_PIN >= 0) pinMode(_ADC_CHANNEL, INPUT);   // これがないと正しく測定できない場合がある。
  delay(100);                                          // wait time when usig parallel capacitor (1uF) for stable measurement
  for (i = 0; i < READ_TIMES; i++) {
    delay(5);
    iAin[i] = readAdc(_ADC_CHANNEL);
  }
  sort(iAin, READ_TIMES);
  Ain = (iAin[MEDIAN_ORDER - 1] + iAin[MEDIAN_ORDER] + iAin[MEDIAN_ORDER + 1]) / 3;
  if (_EXCITE_PIN >= 0) {
    digitalWrite(_EXCITE_PIN, LOW);   // stop supply voltage after measurement
  }
  if (_NTC_CONNECT == NTC_GND) {
    if (Ain <= _ADC_HL) {  // do not reach _EXCITE_VALUE or O may be because using parallel capacitor
      r = _DIV_R * (float)Ain /(float)(_EXCITE_VALUE - Ain);
//      r = _DIV_R / ((float)_ADC_VIN_VALUE / (float)Ain - 1);

    } else {
      return 0;
    }
  } else {
    if (Ain >= _ADC_HL) { // 並列コンデンサを使っているからか、断線しても０にならない。
      r = _DIV_R * (((float)_EXCITE_VALUE/(float)Ain) - 1);
    } else {
      return 0;
    }
  }
  return r - _CABLE_R;
}


uint16_t SHthermistor::readAdc(int16_t adcChannel) {
  return analogRead(adcChannel);
}


float SHthermistor::r2temp(float r) { // culculate temperature from thermistor resistance using Steinhart-Hart equation
  if (r == 0) return TH_ERR_DATA;
  return (1 / (SH_A + SH_B * log(r) + SH_C * pow(log(r), 3)) - 273.15 + _OFFSET_TEMP); // return temperature in Celcius
}


float SHthermistor::temp2r(float t) { // culculate thermistor resistance from temperature using Steinhart-Hart equation
  float T = t + 273.15;
  float x,y;
  
  x = (SH_A - 1/T) / SH_C;
  float SH_BC = pow(SH_B/SH_C, 3);
  y = sqrt(SH_BC/27 + pow(x, 2)/4);
  
  return exp(pow(y - x/2, 1/3.) - pow(y + x/2, 1/3.)); // return resistance in ohm
}


float SHthermistor::readTemp() {
  return r2temp(readR());
}


void SHthermistor::setDivR(float divR) {
  _DIV_R = divR;
}


void SHthermistor::setCableR(float cableR) {
  _CABLE_R = cableR;
}


void SHthermistor::setOffsetTemp(float offsetTemp) {
  _OFFSET_TEMP = offsetTemp;
}


float SHthermistor::getSH_A() {
  return SH_A;
}


float SHthermistor::getSH_B() {
  return SH_B;
}


float SHthermistor::getSH_C() {
  return SH_C;
}


void SHthermistor::setExciteValue(uint32_t exciteValue) {
  _EXCITE_VALUE = exciteValue;
  if (_NTC_CONNECT == NTC_GND) {
    _ADC_HL = _EXCITE_VALUE * 0.98;
  } else {
    _ADC_HL = _EXCITE_VALUE * 0.02;
  }
}


void SHthermistor::sort(uint16_t a[], uint8_t size) {
  for(int i = 0; i < (size - 1); i++) {
    for(int j = 0; j < (size - (i + 1)); j++) {
      if(a[j] > a[j + 1]) {
        int k = a[j];
        a[j] = a[j + 1];
        a[j + 1] = k;
      }
    }
  }
}
