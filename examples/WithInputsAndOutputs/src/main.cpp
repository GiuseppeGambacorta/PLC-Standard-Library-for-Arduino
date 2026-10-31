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
TON onDelay;
TOF offDelay;

void setup() {
    Serial.begin(115200);
}

void loop() {
    const bool buttonPressed = button.isActive();

    onDelay.update(buttonPressed, timerPresetMs);
    offDelay.update(buttonPressed, timerPresetMs);

    if (onDelay.isActive()) {
        tonLed.on();
    } else {
        tonLed.off();
    }

    if (offDelay.isActive()) {
        tofLed.on();
    } else {
        tofLed.off();
    }
}
