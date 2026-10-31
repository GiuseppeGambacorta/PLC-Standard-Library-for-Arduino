#include <plc.h>

DigitalInput button(2, NormalyClosed);
DigitalOutput led(LED_BUILTIN);
R_trig risingTrigger;
TON onDelay;

void setup() {
    Serial.begin(115200);
}

void loop() {
    const bool input = button();

    risingTrigger(input);
    onDelay(input, 1000);

    if (onDelay()) {
        led.on();
    } else {
        led.off();
    }

    if (risingTrigger()) {
        Serial.println("Callable rising edge detected");
    }

    delay(10);
}
