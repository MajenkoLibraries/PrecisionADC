#include <PrecisionADC.h>

// Pin 9 is the ADC chip select
// Pin 10 is the DAC chip select
PrecisionADC adc(9, 10);

void setup() {
  Serial.begin(115200);
  adc.begin();  

  // Let's have a 2.5V reference voltage
  adc.setReference(2500); 
}

void loop() {
  // Get the current voltage in millivolts
  float voltage = adc.readMV();

  Serial.print(F("Voltage: "));

  // Check for an overflow condition
  if (adc.overflow()) {
    Serial.println(F("Too high!"));
  } else {
    Serial.print(voltage);
    Serial.println(F("mV"));
  }
  delay(1000);
}

