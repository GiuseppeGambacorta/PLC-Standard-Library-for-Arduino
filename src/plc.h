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
