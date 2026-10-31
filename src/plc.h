#pragma once

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
