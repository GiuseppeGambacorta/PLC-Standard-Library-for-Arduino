#include <Arduino.h>
#include <plc.h>

#ifndef TRIG_BUTTON_PIN
#define TRIG_BUTTON_PIN 2
#endif

constexpr uint8_t buttonPin = TRIG_BUTTON_PIN;

R_trig risingTrigger;
F_trig fallingTrigger;

void setup() {
    Serial.begin(115200);
    pinMode(buttonPin, INPUT_PULLUP);
}

void loop() {
    const bool buttonPressed = digitalRead(buttonPin) == LOW;

    risingTrigger.update(buttonPressed);
    fallingTrigger.update(buttonPressed);

    if (risingTrigger.isActive()) {
        Serial.println("R_trig: fronte di salita");
    }

    if (fallingTrigger.isActive()) {
        Serial.println("F_trig: fronte di discesa");
    }
}
