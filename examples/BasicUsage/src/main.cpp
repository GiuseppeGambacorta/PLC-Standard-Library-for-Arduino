#include <Arduino.h>
#include <Untitled1.h>

Untitled1 library;
unsigned long lastBlink = 0;
bool ledState = false;

void setup() {
    library.begin();
    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, LOW);
}

void loop() {
    library.update();

    const unsigned long now = millis();
    if (now - lastBlink >= 500) {
        lastBlink = now;
        ledState = !ledState;
        digitalWrite(LED_BUILTIN, ledState ? HIGH : LOW);
    }
}
