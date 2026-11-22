#include <Arduino.h>
#include <math.h>

#define LDR_PIN 4
int adcValue;
float voltage;
int voltageMv;

// вимірюємо ADC на піні з фоторезистором
int readADC()
{
  adcValue = analogRead(LDR_PIN);

  Serial.print("ADC: ");
  Serial.print(adcValue);

  return adcValue;
}

// рахуємо вольтаж
float calculateVoltage(int adcValue)
{
  voltage = adcValue * 3.1 / 4095.0;

  Serial.print(" ----- Voltage: ");
  Serial.print(voltage, 3);
  Serial.print(" V ----- ");

  return voltage;
}

// зчитуємо напругу
int readVoltageMv()
{
  voltageMv = analogReadMilliVolts(LDR_PIN);

  Serial.print("Виміряно  ");
  Serial.print(voltageMv);
  Serial.print(" mV ----- ");

  return voltageMv;
}

// обчислення похибки
void calculateVoltageDeviation(float voltage, int voltageMv)
{
  float deviation = 0;

  float measuredVoltage = voltageMv / 1000.0;
  float difference = fabs(voltage - measuredVoltage);

  if (measuredVoltage > 0)
  {
    deviation = (difference / measuredVoltage) * 100;
  }

  Serial.print("Deviation: ");
  Serial.print(deviation, 2);
  Serial.println(" %");
  return;
}

void setup()
{
  Serial.begin(115200);
}

void loop()
{

  adcValue = readADC();
  voltage = calculateVoltage(adcValue);
  voltageMv = readVoltageMv();
  calculateVoltageDeviation(voltage, voltageMv);

  delay(100);
}
