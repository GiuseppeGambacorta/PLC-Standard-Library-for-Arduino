#include <unity.h>
#include <plc.h>

void setUp(void) {}
void tearDown(void) {}

void test_analog_input_scales_raw_value_to_configured_range() {
    AnalogInput input(0, 0.0f, 100.0f, 1000);
    input.setRawValue(500);

    TEST_ASSERT_EQUAL_INT(500, input.readRaw());
    TEST_ASSERT_FLOAT_WITHIN(0.001f, 50.0f, input.readProcessedValue());
}

void test_analog_input_callable_api_matches_processed_value() {
    AnalogInput input(0, -10.0f, 10.0f, 1000);
    input.setRawValue(250);

    TEST_ASSERT_FLOAT_WITHIN(0.001f, -5.0f, input());
    TEST_ASSERT_FLOAT_WITHIN(
        0.001f,
        input.readProcessedValue(),
        input()
    );
}

void run_all_tests() {
    UNITY_BEGIN();
    RUN_TEST(test_analog_input_scales_raw_value_to_configured_range);
    RUN_TEST(test_analog_input_callable_api_matches_processed_value);
    UNITY_END();
}

#if defined(ARDUINO)
void setup() {
    run_all_tests();
}

void loop() {}
#else
int main() {
    run_all_tests();
    return 0;
}
#endif
