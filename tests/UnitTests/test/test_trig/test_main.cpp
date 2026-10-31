#include <unity.h>
#include <plc.h>

#if !defined(ARDUINO)
#include <chrono>
#include <thread>
#endif

// Obbligatori per Unity
void setUp(void) {}
void tearDown(void) {}

void wait_for_milliseconds(unsigned long milliseconds) {
#if defined(ARDUINO)
    delay(milliseconds);
#else
    std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
#endif
}

// --- Test Case ---

void test_rising_trigger_is_inactive_until_rising_edge() {
    R_trig trigger;

    trigger.update(false);
    TEST_ASSERT_FALSE(trigger.isActive());

    trigger.update(true);
    TEST_ASSERT_TRUE(trigger.isActive());

    trigger.update(true);
    TEST_ASSERT_FALSE(trigger.isActive());
}

void test_rising_trigger_can_fire_again_after_input_goes_low() {
    R_trig trigger;

    trigger(false);
    trigger(true);
    TEST_ASSERT_TRUE(trigger.isActive());
    trigger(false);
    TEST_ASSERT_FALSE(trigger.isActive());
    trigger(true);
    TEST_ASSERT_TRUE(trigger.isActive());
}

void test_falling_trigger_is_inactive_until_falling_edge() {
    F_trig trigger;

    trigger.update(false);
    TEST_ASSERT_FALSE(trigger.isActive());

    trigger.update(true);
    TEST_ASSERT_FALSE(trigger.isActive());

    trigger.update(false);
    TEST_ASSERT_TRUE(trigger.isActive());

    trigger.update(false);
    TEST_ASSERT_FALSE(trigger.isActive());
}

void test_falling_trigger_can_fire_again_after_input_goes_high() {
    F_trig trigger;

    trigger(true);
    trigger(false);
    TEST_ASSERT_TRUE(trigger.isActive());
    trigger(true);
    TEST_ASSERT_FALSE(trigger.isActive());
    trigger(false);
    TEST_ASSERT_TRUE(trigger.isActive());
}

void test_ton_activates_after_input_stays_high_for_preset() {
    TON timer;

    timer.update(false, 20);
    TEST_ASSERT_FALSE(timer.isActive());

    timer.update(true, 20);
    TEST_ASSERT_FALSE(timer.isActive());

    wait_for_milliseconds(30);
    timer.update(true, 20);
    TEST_ASSERT_TRUE(timer.isActive());
}

void test_ton_turns_off_when_input_goes_low() {
    TON timer;

    timer.update(true, 0);
    TEST_ASSERT_TRUE(timer.isActive());

    timer.update(false, 20);
    TEST_ASSERT_FALSE(timer.isActive());
}

void test_tof_stays_active_for_preset_after_falling_edge() {
    TOF timer;

    timer.update(true, 20);
    TEST_ASSERT_TRUE(timer.isActive());

    timer.update(false, 20);
    TEST_ASSERT_TRUE(timer.isActive());

    wait_for_milliseconds(30);
    timer.update(false, 20);
    TEST_ASSERT_FALSE(timer.isActive());
}

void test_tof_turns_on_immediately_when_input_goes_high() {
    TOF timer;

    timer.update(true, 20);
    timer.update(false, 20);
    TEST_ASSERT_TRUE(timer.isActive());

    timer.update(true, 20);
    TEST_ASSERT_TRUE(timer.isActive());
}

// Funzione runner comune
void run_all_tests() {
    UNITY_BEGIN();
    RUN_TEST(test_rising_trigger_is_inactive_until_rising_edge);
    RUN_TEST(test_rising_trigger_can_fire_again_after_input_goes_low);
    RUN_TEST(test_falling_trigger_is_inactive_until_falling_edge);
    RUN_TEST(test_falling_trigger_can_fire_again_after_input_goes_high);
    RUN_TEST(test_ton_activates_after_input_stays_high_for_preset);
    RUN_TEST(test_ton_turns_off_when_input_goes_low);
    RUN_TEST(test_tof_stays_active_for_preset_after_falling_edge);
    RUN_TEST(test_tof_turns_on_immediately_when_input_goes_high);
    UNITY_END();
}

#if defined(ARDUINO)
#include <Arduino.h>

void setup() {
    // 1. Inizializza la porta seriale USB CDC
    Serial.begin(115200);

    // 2. Attendi che il PC si connetta alla porta seriale (timeout 10 secondi)
    unsigned long start = millis();
    while (!Serial && (millis() - start < 10000)) {
        delay(10);
    }

    // 3. Attesa breve per sincronizzare il buffer seriale con PlatformIO
    delay(1000);

    // 4. Avvio dei test
    run_all_tests();
}

void loop() {
    // Vuoto
}

#else
// Se compila per PC locale (ambiente Native)
int main(int argc, char **argv) {
    run_all_tests();
    return 0;
}
#endif