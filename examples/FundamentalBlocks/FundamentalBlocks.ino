#include <plc.h>

constexpr uint8_t buttonPin = 2;
constexpr uint8_t tonLedPin = LED_BUILTIN;
constexpr uint8_t tofLedPin = 12;
constexpr unsigned long presetMs = 1000;

R_trig risingTrigger;
F_trig fallingTrigger;
TON onDelay;
TOF offDelay;

void setup() {
    Serial.begin(115200);
    pinMode(buttonPin, INPUT_PULLUP);
    pinMode(tonLedPin, OUTPUT);
    pinMode(tofLedPin, OUTPUT);
}

void loop() {
    const bool input = digitalRead(buttonPin) == LOW;

    risingTrigger.update(input);
    fallingTrigger.update(input);
    onDelay.update(input, presetMs);
    offDelay.update(input, presetMs);

    digitalWrite(tonLedPin, onDelay.isActive() ? HIGH : LOW);
    digitalWrite(tofLedPin, offDelay.isActive() ? HIGH : LOW);

    if (risingTrigger.isActive()) {
        Serial.println("R_trig: button pressed");
    }
    if (fallingTrigger.isActive()) {
        Serial.println("F_trig: button released");
    }
}
