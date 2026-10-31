#include <Arduino.h>
#include "../../../src/plc.h"

#ifndef ANALOG_INPUT_PIN
#define ANALOG_INPUT_PIN A0
#endif

AnalogInput sensor(ANALOG_INPUT_PIN, 0.0f, 100.0f);

void setup() {
    Serial.begin(115200);
}

void loop() {
    const int rawValue = sensor.readRaw();
    const float processedValue = sensor.readProcessedValue();
    const float callableValue = sensor();

    Serial.print("Raw: ");
    Serial.println(rawValue);
    Serial.print("Processed (readProcessedValue): ");
    Serial.println(processedValue);
    Serial.print("Processed (operator()): ");
    Serial.println(callableValue);

    delay(1000);
}
