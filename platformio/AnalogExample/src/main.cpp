#include <Arduino.h>
#include "../../src/plc.h"

#ifndef ANALOG_INPUT_PIN
#define ANALOG_INPUT_PIN A0
#endif

#ifndef ANALOG_OUTPUT_PIN
#define ANALOG_OUTPUT_PIN 9
#endif

AnalogInput sensor(ANALOG_INPUT_PIN, 0.0f, 100.0f, 1023, 5);
AnalogOutput actuator(ANALOG_OUTPUT_PIN, 0.0f, 100.0f);

void setup() {
    Serial.begin(115200);
}

void loop() {
    const int rawValue = sensor.readRaw();
    const float processedValue = sensor.readProcessedValue();
    const float filteredValue = sensor.readFilteredValue();
    const float callableValue = sensor();

    actuator.writeProcessedValue(filteredValue);

    Serial.print("Raw: ");
    Serial.println(rawValue);
    Serial.print("Processed (readProcessedValue): ");
    Serial.println(processedValue);
    Serial.print("Processed (operator()): ");
    Serial.println(callableValue);
    Serial.print("Filtered (moving average): ");
    Serial.println(filteredValue);
    Serial.print("Output raw: ");
    Serial.println(actuator.readRaw());
    Serial.print("Output processed: ");
    Serial.println(actuator.readProcessedValue());

    delay(1000);
}
