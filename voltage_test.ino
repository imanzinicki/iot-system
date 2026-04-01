#include "HX711.h"

HX711 scale;

// HX711 DT, SCK pins (change to your pins)
#define DOUT 4
#define SCK 5

void setup() {
  Serial.begin(115200);
  scale.begin(DOUT, SCK);
  delay(500);
  Serial.println("HX711 calibration helper");
  // Give the sensor time to settle
  delay(1000);
  // Read zero offset
  long zero = scale.read_average(20);
  Serial.print("Zero (avg 20): ");
  Serial.println(zero);
  Serial.println("Place a known weight now and press ENTER (e.g., 1000 for 1kg)");
}

void loop() {
  if (Serial.available()) {
    // read user-entered known weight in grams
    long knownGrams = Serial.parseInt();
    if (knownGrams <= 0) {
      Serial.println("Enter known weight in grams (e.g., 1000)");
      while (Serial.available()) Serial.read();
      return;
    }
    Serial.print("Using known weight (g): ");
    Serial.println(knownGrams);

    long zero = scale.read_average(50);
    Serial.print("Zero (avg 50): ");/
    Serial.println(zero);

    // Wait a little to stabilize then read with weight
    delay(1000);
    long reading = scale.read_average(50);
    Serial.print("Reading with weight (avg 50): ");
    Serial.println(reading);

    float calib = float(reading - zero) / float(knownGrams);
    Serial.print("Calculated calibration factor: ");
    Serial.println(calib, 6);

    Serial.println("To use: scale.set_scale(calib);");
    Serial.println("Verify with other known weights and adjust averaging if noisy.");
    while (Serial.available()) Serial.read();
  }
}
