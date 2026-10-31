#include <Arduino.h>
#include "../../src/plc.h"

#ifndef TRIG_BUTTON_PIN
#define TRIG_BUTTON_PIN 2
#endif

#ifndef TON_LED_PIN
#define TON_LED_PIN LED_BUILTIN
#endif

#ifndef TOF_LED_PIN
#if defined(ARDUINO_OPTA)
#define TOF_LED_PIN LED_D0
#else
#define TOF_LED_PIN 12
#endif
#endif

constexpr uint8_t buttonPin = TRIG_BUTTON_PIN;
constexpr uint8_t tonLedPin = TON_LED_PIN;
constexpr uint8_t tofLedPin = TOF_LED_PIN;
constexpr unsigned long timerPresetMs = 1000;

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
    const bool buttonPressed = digitalRead(buttonPin) == LOW;

    risingTrigger.update(buttonPressed);
    fallingTrigger.update(buttonPressed);
    onDelay.update(buttonPressed, timerPresetMs);
    offDelay.update(buttonPressed, timerPresetMs);

    digitalWrite(tonLedPin, onDelay.isActive() ? HIGH : LOW);
    digitalWrite(tofLedPin, offDelay.isActive() ? HIGH : LOW);

    if (risingTrigger.isActive()) {
        Serial.println("R_trig: button pressed");
    }

    if (fallingTrigger.isActive()) {
        Serial.println("F_trig: button released");
    }
}
