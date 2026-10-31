#pragma once

#if defined(ARDUINO)
#include <Arduino.h>
#else
#include <chrono>
#endif

namespace plc_detail {

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
