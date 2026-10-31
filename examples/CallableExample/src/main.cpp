#include <Arduino.h>
#include "../../../src/plc.h"

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

constexpr unsigned long timerPresetMs = 1000;

DigitalInput button(TRIG_BUTTON_PIN, NormalyClosed);
DigitalOutput tonLed(TON_LED_PIN);
DigitalOutput tofLed(TOF_LED_PIN);
R_trig risingTrigger;
F_trig fallingTrigger;
TON onDelay;
TOF offDelay;

void setup() {
    Serial.begin(115200);
}

void loop() {
    const bool buttonPressed = button();

    onDelay(buttonPressed, timerPresetMs);
    offDelay(buttonPressed, timerPresetMs);
    risingTrigger(buttonPressed);
    fallingTrigger(buttonPressed);

    if (onDelay()) {
        tonLed.on();
    } else {
        tonLed.off();
    }

    if (offDelay()) {
        tofLed.on();
    } else {
        tofLed.off();
    }

    if (risingTrigger()) {
        Serial.println("R_trig: pulsante premuto");
    }

    if (fallingTrigger()) {
        Serial.println("F_trig: pulsante rilasciato");
    }
}
