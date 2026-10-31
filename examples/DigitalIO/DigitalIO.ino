#include <plc.h>

DigitalInput button(2, NormalyClosed);
DigitalOutput led(LED_BUILTIN);

void setup() {
    Serial.begin(115200);
}

void loop() {
    if (button.isActive()) {
        led.on();
    } else {
        led.off();
    }

    delay(10);
}
