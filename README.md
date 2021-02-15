# SHthermistor
 v1.1.0  citriena Dec. 2020

## Introduction
**SHthermistor** is an Arduino library that supports temperature measurements with NTC thermistor based on Steinhart-Hart equation.

## Features
* **SHthermistor** calculates temperature (T) from a thermistor resistance (R) usng Steinhart-Hart equation shown below.
```math
 1/T = A + B*ln(R) + C*(ln(R))^3
```
The deviation between datasheet values and Steinhart-Hart equation is less than 0.01 °C from 0 to 50°C in case of
103AT-11 thermistor (SEMITEC Corporation).
* use median value among 11 measurements, not overall average, to avoid error caused by surge pulse.

## Usage
### Circuit

Ether of the circuits below is available.
````
 1. Vdd(excitePin)---NTC thermistor---adcPin---SERIES_RESISTOR---GND
 2. Vdd(excitePin)---SERIES_RESISTOR---adcPin---NTC thermistor---GND
````
### Constructor
````
SHthermistor(float SH_T1, float SH_T2, float SH_T3, float SH_R1, float SH_R2, float SH_R3, float divR, int8_t adcPin, NTC_CONNECT_t ntcConnect, int8_t excitePin, float offsetT, uint32_t exciteValue)
````
* **SH\_T1, SH\_T2, SH\_T3:** Low, mid, and high temperature (Celcius) of measureing range.
* **SH\_R1, SH\_R2, SH\_R3:** Thermistor resistance (ohm) at SH_T1, SH_T2, and SH_T3.
* **divR:** Resistance value (ohm) of the series divider resistor.
* **adcPin:** Analog pin connected to the thermistor and the series resistor.
* **ntcConnect:** Connection of the thermistor and the series resistor.
  * NTC_EXCITE: The thermistor is connected to excitePin (circuit 1).
  * NTC_GND: The thermistor is connected to GND (circuit 2).
* **excitePin(optional):** Voltage supply pin. When excitePin is designated the voltage will be supplied only during measurement. Default value is -1 (do not control).
* **offsetTemp:** Offset value added to the calculated temperature
* **exciteValue (optional)** : ADC read value of excitePin (in case of Arduino excitePin = VREF( = Vdd)).
  * ADC_10_BIT_VALUE: 10 bit (default)
  * ADC_12_BIT_VALUE: 12 bit
  * ADC_14_BIT_VALUE: 14 bit
  * ADC_16_BIT_VALUE: 16 bit
  * set EXCITE_VALUE directly in case of using external ADC with internal VREF etc.

If you want to set coefficients of Steinhart and Hart equation directly use following constructor.
````
SHthermistor(float shA, float shB, float shC, float divR, uint8_t adcPin, NTC_CONNECT_t ntcConnect, int8_t excitePin, float offsetT, uint32_t exciteValue);
````

### Functions
````
float readTemp();
````
Returns thermistor temperature.

````
float readR();
````
Returns thermistor resitance.
````
float r2temp(float r);
````
Returns temperature calculated from thermistor resistance.

````
void setDivR(float divR);
````
Set series resistance value.

````
void setCableR(float cableR);
````
Set resistance value of the cable to the thermistor.

````
void setOffsetTemp(float offsetT);
````
Set offset value added to the calculated temperature.

### Using external ADC
Arduino Uno R3 have ADC of 10 bits. It is sufficient for 0.5 degree resolution. But if you need 0.1 degree resolution at least ADC of 12 bits is necessary. SHthermistorMCP320X is a sample library containing SHthermistorMCP320X class, subclass of SHthermistor, for using Microchip MCP320X (MCP3201/3202/3204/3208) instead of Arduino internal ADC without modifying SHthermistor library.

SHthermistorMCP320X class inherets all the attributes of the SHthermistor class, have new member function of begin() to initialize MCP320X and overrides readAdc() to read MCP320X.

## References
http://www.nktherm.com/tec/linearize.html (link rot) Steinhart and Hart 式によるサーミスタ抵抗値の温度変換

John M. Zurbuchen. Precision thermistor thermometry. Measurement Science Conference Tutorial: Thermometry-Fundamentals and Practice, 2000.

https://edwardmallon.files.wordpress.com/2017/04/ntc-steinhart_and_hart_calculator.xls

## Releases

### 1.0.0 - Jun. 18, 2020

### 1.1.0 - Dec. 31, 2020
* added setCableR() function.
