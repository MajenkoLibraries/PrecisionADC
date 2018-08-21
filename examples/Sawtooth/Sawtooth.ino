// Generate a crude Sawtooth wave on the
// VOut pin

#include <PrecisionADC.h>

// Pin 9 is the ADC chip select
// Pin 10 is the DAC chip select
PrecisionADC adc(9, 10);

void setup() {
  adc.begin();  
}

void loop() {
  static uint16_t mv = 0;

  // Set the current output voltage in millivolts
  adc.setVOut(mv);

  mv += 10; // Let's do 10mV steps

  // The highest voltage we can do is 4095mV
  // You could use the % operator, but that
  // takes decades by comparison to a simple
  // check-and-subtract.
  if (mv > 4095) {
    mv -= 4096;
  }

  // A short delay.
  delay(1);
}

