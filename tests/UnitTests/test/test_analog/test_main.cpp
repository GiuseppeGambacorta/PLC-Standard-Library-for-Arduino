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

void test_analog_input_filters_samples_with_moving_average() {
    AnalogInput input(0, 0.0f, 100.0f, 1000, 3);

    input.setRawValue(100);
    TEST_ASSERT_FLOAT_WITHIN(0.001f, 10.0f, input.readFilteredValue());

    input.setRawValue(300);
    TEST_ASSERT_FLOAT_WITHIN(0.001f, 20.0f, input.readFilteredValue());

    input.setRawValue(500);
    TEST_ASSERT_FLOAT_WITHIN(0.001f, 30.0f, input.readFilteredValue());

    input.setRawValue(700);
    TEST_ASSERT_FLOAT_WITHIN(0.001f, 50.0f, input.readFilteredValue());
}

void test_analog_output_scales_processed_value_to_raw_value() {
    AnalogOutput output(0, 0.0f, 100.0f, 1000);

    output.writeProcessedValue(25.0f);

    TEST_ASSERT_EQUAL_INT(250, output.readRaw());
    TEST_ASSERT_FLOAT_WITHIN(0.001f, 25.0f, output.readProcessedValue());
}

void test_analog_output_clamps_values_outside_configured_range() {
    AnalogOutput output(0, 0.0f, 100.0f, 1000);

    output(-10.0f);
    TEST_ASSERT_EQUAL_INT(0, output.readRaw());

    output.writeProcessedValue(120.0f);
    TEST_ASSERT_EQUAL_INT(1000, output.readRaw());
}

void run_all_tests() {
    UNITY_BEGIN();
    RUN_TEST(test_analog_input_scales_raw_value_to_configured_range);
    RUN_TEST(test_analog_input_callable_api_matches_processed_value);
    RUN_TEST(test_analog_input_filters_samples_with_moving_average);
    RUN_TEST(test_analog_output_scales_processed_value_to_raw_value);
    RUN_TEST(test_analog_output_clamps_values_outside_configured_range);
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
