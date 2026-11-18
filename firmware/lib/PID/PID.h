#pragma once
// Simple PID controller with derivative-on-measurement, output clamping
// and integral anti-windup. Call update() at a fixed rate.

class PID {
public:
    PID(float kp, float ki, float kd, float outMin, float outMax)
        : kp_(kp), ki_(ki), kd_(kd), outMin_(outMin), outMax_(outMax) {}

    void setGains(float kp, float ki, float kd) { kp_ = kp; ki_ = ki; kd_ = kd; }

    void reset() { integral_ = 0.0f; prevMeas_ = 0.0f; first_ = true; }

    // setpoint and measurement in the same units (e.g. degrees), dt in seconds
    float update(float setpoint, float measurement, float dt) {
        if (dt <= 0.0f) return lastOut_;
        float error = setpoint - measurement;

        // Derivative on measurement avoids a "kick" when the setpoint changes
        float dMeas = first_ ? 0.0f : (measurement - prevMeas_) / dt;
        prevMeas_ = measurement;
        first_ = false;

        float p = kp_ * error;
        float d = -kd_ * dMeas;

        // Only integrate if it won't push an already-saturated output further (anti-windup)
        float candidateI = integral_ + ki_ * error * dt;
        float out = p + candidateI + d;
        if ((out > outMax_ && error > 0) || (out < outMin_ && error < 0)) {
            out = p + integral_ + d;  // keep old integral
        } else {
            integral_ = candidateI;
        }

        if (out > outMax_) out = outMax_;
        if (out < outMin_) out = outMin_;
        lastOut_ = out;
        return out;
    }

private:
    float kp_, ki_, kd_;
    float outMin_, outMax_;
    float integral_ = 0.0f;
    float prevMeas_ = 0.0f;
    float lastOut_ = 0.0f;
    bool first_ = true;
};
