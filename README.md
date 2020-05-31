# SHthermistor
 v1.0  citriena May 2020

## Introduction
**SHthermistor** is an Arduino library that supports temperature measurements with NTC thermistor based on Steinhart-Hart equation.

## Features
* **SHthermistor** calculates temperature (T) from a thermistor resistance (R) usng Steinhart-Hart equation shown below.
```math
 1/T = A + B*ln(R) + C*(ln(R))^3
```

## Usage
### Connection

Ether of the connection below is available.
````
 1. Vdd(excitePin)---NTC thermistor---adcPin---SERIES_RESISTOR---GND
 2. Vdd(excitePin)---SERIES_RESISTOR---adcPin---NTC thermistor---GND
````
### Constructor
````
SHthermistor(float SH_T1, float SH_T2, float SH_T3, float SH_R1, float SH_R2, float SH_R3, int8_t adcPin, float divR, NTC_CONNECT_t ntcConnect, int8_t vinPin, float offsetT, uint32_t exciteValue)
````
* **SH\_T1, SH\_T2, SH\_T3:** low, mid, and high temperature (Celcius)

* **SH\_R1, SH\_R2, SH\_R3:** thermistor resistance (ohm) at SH_T1, SH_T2, SH_T3
* **adcPin:** analog pin connected to thermistor and series resistor
* **divR:** resistance value (ohm) of series divider resistor
* **ntcConnect:** connection of thermistor and series resistor
  * NTC_EXCITE: Thermistor is connected to excitePin (connecton 1).
  * NTC_GND: Thermistor is connected to GND (connection 2).
* **offsetTemp:** offset value added to calculated temperature
* **exciteValue (optional)** : ADC read value of excitePin (in case of Arduino excitePin = VREF( = Vdd))
  * ADC_10_BIT_VALUE: 10 bit (default)
  * ADC_12_BIT_VALUE: 12 bit
  * ADC_14_BIT_VALUE: 14 bit
  * ADC_16_BIT_VALUE: 16 bit
  * set EXCITE_VALUEvalue directly in case of using external ADC with internal VREF
* **excitePin(optional):** Voltage supply pin. When you designate excitePin the voltage will be supplied only during measurement.

### Functions
````
float readTemp();
````
returns thermistor temperature

use median among 11 thermistor resisstance measurements to caclurete temperature

````
float readR();
````
returns thermistor resitance

Most of the case you do not need to use readR().

````
float r2temp(float r);
````
returns calculated temperature from thermistor resistance

Most of the case you do not need to use r2temp().

````
void setDivR(float divR);
````
set series resistance

Series resistance can be set in Constructor so most of the case setDivR() is not necessary.

````
void setOffsetTemp(float offsetT);
````
set offset value added to calculated temperature

Offset value can be set in Constructor so most of the case setOffsetTemp() is not necessary.


### Using external ADC
Arduino Uno R3 have ADC of 10 bits. It is sufficient for 0.5 degree resolution. But if you need 0.1 degree resolution at least ADC of 12 bits is necessary.. SHthermistorMCP320X is a sample library containing SHthermistorMCP320X class, subclass of SHthermistor, for using Microchip MCP320X (MCP3201/3202/3204/3208) instead of Arduino internal ADC without modifying SHthermistor library.

SHthermistorMCP320X class inherets all the attributes of the SHthermistor class, have new member function of begin() to initialize MCP320X and overrides readAdc() to read MCP320X.

## References
http://www.nktherm.com/tec/linearize.html (linkrot) Steinhart and Hart 式によるサーミスタ抵抗値の温度変換

John M. Zurbuchen. Precision thermistor thermometry. Measurement Science Conference Tutorial: Thermometry-Fundamentals and Practice, 2000.

https://edwardmallon.files.wordpress.com/2017/04/ntc-steinhart_and_hart_calculator.xls



## 概要
**SHthermistor** はNTCサーミスタで温度を測定するためのArduinoライブラリです。

## 特徴
* Steinhart and Hart 式による抵抗値-温度変換

  * 以下に示すSteinhart and Hart 式を使ってサーミスタの抵抗値から温度を算出します。Steinhart and Hart 式は私が知る限り温度とサーミスタの抵抗値との関係を最もよくあらわす関係式です。
```
1/T = A + B\*ln(R) + C\*(ln(R))^3
```
  * Steinhart and Hart 式の利用にもB定数から近似する方法等いろいろあるようですが、きちんと三元連立方程式を解いてSteinhart and Hart式の係数を出しています。サーミスタによって異なるかもしれませんが、私が主に使っているSEMITEC株式会社103AT-11では 0, 25, 50℃で係数を出せばその範囲でのデータシートとの誤差は**0.01℃**以内です。


* 1回の測定で11回計測し、中央値を使って温度変換
  * 平均値だとスパイクノイズが入ったときに誤差が大きくなると考え、中央値で計算するようにしています。
* 測定時のみサーミスタに通電し、消費電流削減、および自己発熱による誤差抑制が可能
  * 自己発熱による誤差抑制にはどの程度効果があるかわかりません。

## 使い方
### 接続方法

以下のどちらの接続も可能です。
````
1. Vdd(excitePin)---NTCサーミスタ---adcPin---分圧抵抗---GND
2. Vdd(excitePin)---分圧抵抗---adcPin---NTCサーミスタ---GND
````
言うまでもありませんが、分圧抵抗には温度係数が小さく精度の高い金属被膜抵抗等を使います。

### コンストラクタ
````
SHthermistor(float SH_T1, float SH_T2, float SH_T3, float SH_R1, float SH_R2, float SH_R3, int8_t adcPin, float divR, NTC_CONNECT_t ntcConnect, int8_t vinPin, float offsetT, uint32_t exciteValue);

````
* **SH\_T1, SH\_T2, SH\_T3:** 使用温度範囲を含む3点の温度（℃）
  * 使用温度範囲の概ね最低、中央、最高温度
  * 間隔が狭いほどその間の近似の精度が高くなりますので、実際の測定温度を考慮して設定します。
* **SH\_R1, SH\_R2, SH\_R3:** SH_T1, SH_T2, SH_T3のサーミスタの抵抗値（Ω）
  * サーミスタのデータシートを参照して設定
* **adcPin:** サーミスタ抵抗値測定用読み取りアナログピン
* **divR:** サーミスタ抵抗値測定用分圧抵抗値（Ω）
  * 分圧抵抗値とサーミスタ抵抗値が近いほど温度による出力変化が大きいので、それを考慮して分圧抵抗値を決めます。
  * 気温を測定するのであれば、一般的に25℃時のサーミスタの抵抗値と同じのを使います。
* **ntcConnect:** 分圧抵抗とサーミスタの接続方法
  * NTC_EXCITE: サーミスタがexcitePin側（接続方法の1）
  * NTC_GND: サーミスタがGND側（接続方法の2）
* **int8_t excitePin(オプション):** サーミスタ給電ピン
  * 指定すると測定時のみexcitePinに給電します。
  * デフォルト値は「-1」（制御しない）です。
* **offsetTemp:** 測定温度補正値（℃）
  * 計算値にこの補正値を加算して測定値とします。
* **exciteValue(オプション):** ADC(ADコンバータ）のexcitePin 読み取り値
  * 以下の設定ができます。
    * ADC_10BIT_VALUE（デフォルト）
    * ADC_12BIT_VALUE
    * ADC_14BIT_VALUE
    * ADC_16BIT_VALUE
    * 値の直接指定（ADコンバータのVREFとexcitePinが異なる場合等）

  * Arduino UNO R3のADCビット数は10なのでデフォルト値のままで良いですが、Arduino DUEなどは12ビットですのでこの設定を行う必要があります。

例えば、秋月電子商会で扱っている　[SEMITEC株式会社103AT-11](http://akizukidenshi.com/catalog/g/gP-07257/)の場合は、
````
SHthermistor thermistor(0, 25, 50, 27280, 10000, 4160, 1, 10000, NTC_GND, 9);
````
みたいに指定します。

### 機能
````
float readTemp();
````
サーミスタの温度を測定します。設定したオフセット値が反映されます。基本的にはこのreadTemp();を使います。
11回測定し、中央値を使って温度を計算します。

````
float readR();
````
サーミスタの抵抗値を返します。
普通は使う必要はありません。
````
float r2temp(float r);
````
引数に指定したサーミスタの抵抗値から温度を返します。補正値が反映されます。

普通は使う必要はありません。

````
void setDivR(float divR);
````
測定用の分圧抵抗値を設定します。

普通は使う必要はありません。

分圧抵抗値は基本的にはコンストラクタで設定しますが、測定精度を高めるために正確な抵抗値を使いたい場合、
装置毎に設定を変えてコンパイルするのは面倒なのでArduinoのEEPROMに設定を書き込んでおき、それを読み込んで
装置毎に正確な抵抗値を設定する場合等に使います。ただ現実問題として、ここで設定できるほど正確に抵抗値を測定するのは容易ではありませんが。
````
void setOffsetTemp(float offsetT);
````
温度の補正値を設定します。

普通は使う必要はありません。

これも分圧抵抗値と同様に基本的にはコンストラクタで設定しますが、メニューで設定できるようにする場合、もしくは装置毎にArduinoのEEPROMに保存した設定値を読み込んで設定する場合等に使用します。

### 別途外部ADコンバータを使う方法
Arduino UNO R3のADコンバータビット数は10です。一般的な測定には十分ですが、0.1℃の分解能で測定したい場合には不足です。最低でも12ビット、できれば16ビットは必要です。
ADコンバータのビット数が12のDUEを使ってもよいのですが、ここでは別途ビット数の多いADコンバータを使う方法を説明します

SHthermistorクラスのメンバ関数であるreadAdc() （ADコンバータ読み取り関数）は virtual指定してあります（仮想関数）。このため、派生クラスで再定義（オーバーライド）できます。これを利用して、使用するADコンバータ用にSHthermistorの派生クラスを作成し、readAdc()を再定義すればSHthermistorを書き換えることなく別途ADコンバータが利用できます。必要に応じ、begin() 等メンバ関数を追加してADコンバータの初期化を行ないます。

#### 外部ADコンバータ接続方法
ADコンバータによって接続方法が異なります。概要だけ説明します。
* VddがVREFを兼ねているもの
  * adcPinに換えてADコンバータの入力を接続するだけでば使えます。
* VREF端子があるもの
  * adcPinに換えてADコンバータの入力を接続するとともに、VREF端子をVddもしくはexcitePinに接続します。
* 内部VREF
  * 2ch以上必要です。
  * 内部VREF以下の安定電圧を別途用意してexcitePinの代用とします。
  * 1chで初期化時、もしくはreadAdc() 内で上の代用excitePinを読み取り、exciteValueとして setExciteValue(uint32_t exciteValue); で設定します。
  * もう1chは readAdc(); 内でadcPinを読み取り、値を返します。
  * このようにすれば使えるはずですが、面倒ですので上記2つのどちらかを使えるADコンバータを使った方が簡単です。


#### 外部ADコンバータ使用例

Microchip MCP3204をADコンバータとして使う場合用に作成したのがSHthermistorMCP320X.h, SHthermistorMCP320X.cpp です。MCP3201/3202/3208でも変更無しで使えると思います。

これらのファイルでは、SHthermistorから派生したSHthermistorMCP320Xクラスが定義されています。SHthermistorMCP320Xクラスでは新たなメンバ関数として
````
void begin(int8_t SELPIN, int8_t channel); ：ADコンバータの初期化
````
* SELPIN: MCP3204 のChipSelect に接続するピン（SPI用）
* channel: MCP3204 で使うチャンネル

を定義するとともに、SHthermistorから継承した
````
uint16_t readAdc(); ：ADコンバータ読み取り
````
を再定義してあります。OOPは付け焼き刃なのでこれが適切な方法かわかりませんが、一応うまく動くようです。

これらの使い方はサンプルスケッチを見てください。
