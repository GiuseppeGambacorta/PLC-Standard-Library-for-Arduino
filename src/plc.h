#pragma once

#if defined(ARDUINO)
#include <Arduino.h>
#else
#include <chrono>
#endif

namespace plc_detail {

constexpr int defaultAnalogMaxValue() {
#if defined(ARDUINO_ARCH_ESP32)
    return 4095;
#else
    return 1023;
#endif
}

constexpr int defaultAnalogOutputMaxValue() {
    return 255;
}

inline unsigned long now() {
#if defined(ARDUINO)
    return millis();
#else
    using clock = std::chrono::steady_clock;
    static const auto start = clock::now();
    return static_cast<unsigned long>(
        std::chrono::duration_cast<std::chrono::milliseconds>(
            clock::now() - start
        ).count()
    );
#endif
}

} // namespace plc_detail

class Trig {
public:
    virtual ~Trig() = default;
    virtual void update(bool input) = 0;
    virtual bool isActive() const = 0;

    void operator()(bool input) {
        update(input);
    }

    bool operator()() const {
        return isActive();
    }
};

class R_trig final : public Trig {
public:
    void update(bool input) override {
        if (interlock_) {
            output_ = false;
        }

        if (!input && interlock_) {
            interlock_ = false;
        }

        if (input && !interlock_) {
            output_ = true;
            interlock_ = true;
        }
    }

    bool isActive() const override {
        return output_;
    }

private:
    bool interlock_ = false;
    bool output_ = false;
};

class F_trig final : public Trig {
public:
    void update(bool input) override {
        if (input) {
            interlock_ = true;
        }

        trig_.update(!input && interlock_);
    }

    bool isActive() const override {
        return trig_.isActive();
    }

private:
    R_trig trig_;
    bool interlock_ = false;
};

class TON {
public:
    void update(bool input, unsigned long presetMs) {
        presetMs_ = presetMs;
        rising_.update(input);

        if (rising_.isActive()) {
            startMs_ = plc_detail::now();
            timing_ = true;
            output_ = false;
        }

        if (!input) {
            timing_ = false;
            output_ = false;
            return;
        }

        if (timing_ && elapsed() >= presetMs_) {
            timing_ = false;
            output_ = true;
        }
    }

    void operator()(bool input, unsigned long presetMs) {
        update(input, presetMs);
    }

    bool operator()() const {
        return isActive();
    }

    bool isActive() const {
        return output_;
    }


    unsigned long elapsedTime() const {
        return timing_ ? elapsed() : (output_ ? presetMs_ : 0);
    }

private:
    unsigned long elapsed() const {
        return plc_detail::now() - startMs_;
    }

    R_trig rising_;
    unsigned long presetMs_ = 0;
    unsigned long startMs_ = 0;
    bool timing_ = false;
    bool output_ = false;
};

class TOF {
public:
    void update(bool input, unsigned long presetMs) {
        presetMs_ = presetMs;
        falling_.update(input);

        if (input) {
            timing_ = false;
            output_ = true;
            return;
        }

        if (falling_.isActive()) {
            startMs_ = plc_detail::now();
            timing_ = true;
        }

        if (timing_ && elapsed() >= presetMs_) {
            timing_ = false;
            output_ = false;
        }
    }

    void operator()(bool input, unsigned long presetMs) {
        update(input, presetMs);
    }

    bool operator()() const {
        return isActive();
    }

    bool isActive() const {
        return output_;
    }

    unsigned long elapsedTime() const {
        return timing_ ? elapsed() : (output_ ? 0 : presetMs_);
    }

private:
    unsigned long elapsed() const {
        return plc_detail::now() - startMs_;
    }

    F_trig falling_;
    unsigned long presetMs_ = 0;
    unsigned long startMs_ = 0;
    bool timing_ = false;
    bool output_ = false;
};

enum NormalState {
    NormalyOpen,
    NormalyClosed
};

class DigitalInput {
public:
    explicit DigitalInput(int pin, NormalState normalState = NormalyOpen)
        : pin_(pin), normalState_(normalState) {
#if defined(ARDUINO)
        pinMode(pin_, INPUT);
#endif
    }

    bool operator()() const {
        return isActive();
    }

    bool isActive() const {
#if defined(ARDUINO)
        const bool state = digitalRead(pin_) == HIGH;
        return normalState_ == NormalyClosed ? !state : state;
#else
        return false;
#endif
    }

private:
    int pin_;
    NormalState normalState_;
};

class DigitalOutput {
public:
    explicit DigitalOutput(int pin)
        : pin_(pin) {
#if defined(ARDUINO)
        pinMode(pin_, OUTPUT);
#endif
    }

    void on() {
#if defined(ARDUINO)
        digitalWrite(pin_, HIGH);
#endif
    }

    void off() {
#if defined(ARDUINO)
        digitalWrite(pin_, LOW);
#endif
    }

    bool isActive() const {
#if defined(ARDUINO)
        return digitalRead(pin_) == HIGH;
#else
        return false;
#endif
    }

private:
    int pin_;
};

class AnalogInput {
public:
    static constexpr int MaxFilterSamples = 16;

    explicit AnalogInput(
        int pin,
        float startRange = 0.0f,
        float endRange = static_cast<float>(plc_detail::defaultAnalogMaxValue()),
        int maxAnalogValue = plc_detail::defaultAnalogMaxValue(),
        int filterSize = 1
    )
        : pin_(pin),
          startRange_(startRange),
          endRange_(endRange),
          maxAnalogValue_(
              maxAnalogValue > 0
                  ? maxAnalogValue
                  : plc_detail::defaultAnalogMaxValue()
          ),
          filterSize_(normalizeFilterSize(filterSize)) {
#if defined(ARDUINO)
        pinMode(pin_, INPUT);
#endif
    }

    int readRaw() const {
#if defined(ARDUINO)
        return analogRead(pin_);
#else
        return rawValue_;
#endif
    }

    float readProcessedValue() const {
        if (startRange_ >= endRange_) {
            return 0.0f;
        }

        return scaleRawValue(static_cast<float>(readRaw()));
    }

    float readFilteredValue() const {
        if (startRange_ >= endRange_) {
            return 0.0f;
        }

        filterSamples_[filterIndex_] = readRaw();
        filterIndex_ = (filterIndex_ + 1) % filterSize_;
        if (filterCount_ < filterSize_) {
            ++filterCount_;
        }

        long total = 0;
        for (int index = 0; index < filterCount_; ++index) {
            total += filterSamples_[index];
        }

        return scaleRawValue(
            static_cast<float>(total) / static_cast<float>(filterCount_)
        );
    }

    void setFilterSize(int filterSize) const {
        filterSize_ = normalizeFilterSize(filterSize);
        filterIndex_ = 0;
        filterCount_ = 0;
    }

    int filterSize() const {
        return filterSize_;
    }

    float operator()() const {
        return readProcessedValue();
    }

#if !defined(ARDUINO)
    void setRawValue(int rawValue) {
        rawValue_ = rawValue;
    }
#endif

private:
    static int normalizeFilterSize(int filterSize) {
        if (filterSize < 1) {
            return 1;
        }
        return filterSize > MaxFilterSamples ? MaxFilterSamples : filterSize;
    }

    float scaleRawValue(float raw) const {
        const float normalized = raw / static_cast<float>(maxAnalogValue_);
        return startRange_ + normalized * (endRange_ - startRange_);
    }

    int pin_;
    float startRange_;
    float endRange_;
    int maxAnalogValue_;
    mutable int filterSize_;
    mutable int filterIndex_ = 0;
    mutable int filterCount_ = 0;
    mutable int filterSamples_[MaxFilterSamples] = {};
#if !defined(ARDUINO)
    int rawValue_ = 0;
#endif
};

class AnalogOutput {
public:
    explicit AnalogOutput(
        int pin,
        float startRange = 0.0f,
        float endRange = static_cast<float>(plc_detail::defaultAnalogOutputMaxValue()),
        int maxAnalogValue = plc_detail::defaultAnalogOutputMaxValue()
    )
        : pin_(pin),
          startRange_(startRange),
          endRange_(endRange),
          maxAnalogValue_(
              maxAnalogValue > 0
                  ? maxAnalogValue
                  : plc_detail::defaultAnalogOutputMaxValue()
          ) {
#if defined(ARDUINO)
        pinMode(pin_, OUTPUT);
#endif
    }

    void writeRaw(int rawValue) {
        rawValue_ = clampRawValue(rawValue);
#if defined(ARDUINO)
        analogWrite(pin_, rawValue_);
#endif
    }

    void writeProcessedValue(float value) {
        if (startRange_ >= endRange_) {
            writeRaw(0);
            return;
        }

        const float normalized =
            (value - startRange_) / (endRange_ - startRange_);
        writeRaw(static_cast<int>(normalized * maxAnalogValue_));
    }

    void operator()(float value) {
        writeProcessedValue(value);
    }

    int readRaw() const {
        return rawValue_;
    }

    float readProcessedValue() const {
        if (startRange_ >= endRange_) {
            return 0.0f;
        }

        const float normalized =
            static_cast<float>(rawValue_) / maxAnalogValue_;
        return startRange_ + normalized * (endRange_ - startRange_);
    }

    bool isActive() const {
        return rawValue_ > 0;
    }

private:
    int clampRawValue(int rawValue) const {
        if (rawValue < 0) {
            return 0;
        }
        if (rawValue > maxAnalogValue_) {
            return maxAnalogValue_;
        }
        return rawValue;
    }

    int pin_;
    float startRange_;
    float endRange_;
    int maxAnalogValue_;
    int rawValue_ = 0;
};
