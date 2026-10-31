#include <plc.h>

AnalogInput sensor(A0, 0.0f, 100.0f, 1023, 5);
AnalogOutput actuator(9, 0.0f, 100.0f);

void setup() {
    Serial.begin(115200);
}

void loop() {
    const int rawValue = sensor.readRaw();
    const float processedValue = sensor.readProcessedValue();
    const float filteredValue = sensor.readFilteredValue();

    actuator.writeProcessedValue(filteredValue);

    Serial.print("Raw: ");
    Serial.println(rawValue);
    Serial.print("Processed: ");
    Serial.println(processedValue);
    Serial.print("Filtered: ");
    Serial.println(filteredValue);
    Serial.print("Output raw: ");
    Serial.println(actuator.readRaw());

    delay(1000);
}
