// ESP32 firmware: levelling bench test
// IMU on the end effector -> two PID loops -> wrist pitch & roll servos.
// TODO: replace readImu() with the real IMU driver (BNO085 / MPU-6050).

#include <Arduino.h>
#include <ESP32Servo.h>
#include "PID.h"

constexpr int PIN_SERVO_PITCH = 18;
constexpr int PIN_SERVO_ROLL  = 19;
constexpr float LOOP_HZ = 250.0f;
constexpr uint32_t LOOP_US = (uint32_t)(1e6f / LOOP_HZ);

// Servo neutral (level) positions in degrees: calibrate on the real hardware
constexpr float PITCH_NEUTRAL = 90.0f;
constexpr float ROLL_NEUTRAL  = 90.0f;

// Output = correction in servo degrees, limited to +/-30 deg
PID pitchPid(1.0f, 0.0f, 0.0f, -30.0f, 30.0f);
PID rollPid (1.0f, 0.0f, 0.0f, -30.0f, 30.0f);

Servo servoPitch, servoRoll;
bool levelling = true;

struct Attitude { float pitch; float roll; };

Attitude readImu() {
    // Placeholder: return measured plate pitch/roll in degrees
    return {0.0f, 0.0f};
}

void handleSerial() {
    // Minimal subset of docs/serial-protocol.md: "K P kp ki kd", "L 0/1"
    if (!Serial.available()) return;
    String line = Serial.readStringUntil('\n');
    line.trim();
    if (line.startsWith("K ")) {
        char axis; float kp, ki, kd;
        if (sscanf(line.c_str(), "K %c %f %f %f", &axis, &kp, &ki, &kd) == 4) {
            if (axis == 'P') pitchPid.setGains(kp, ki, kd);
            if (axis == 'R') rollPid.setGains(kp, ki, kd);
        }
    } else if (line.startsWith("L ")) {
        levelling = line.charAt(2) == '1';
        pitchPid.reset();
        rollPid.reset();
    }
}

void setup() {
    Serial.begin(115200);
    servoPitch.attach(PIN_SERVO_PITCH);
    servoRoll.attach(PIN_SERVO_ROLL);
    servoPitch.write(PITCH_NEUTRAL);
    servoRoll.write(ROLL_NEUTRAL);
}

void loop() {
    static uint32_t last = micros();
    static uint32_t lastTelemetry = 0;
    uint32_t now = micros();
    if (now - last < LOOP_US) { handleSerial(); return; }
    float dt = (now - last) * 1e-6f;
    last = now;

    Attitude a = readImu();
    if (levelling) {
        // Setpoint is 0 deg tilt; the sign depends on servo mounting, so flip if it runs away
        float pCorr = pitchPid.update(0.0f, a.pitch, dt);
        float rCorr = rollPid.update(0.0f, a.roll, dt);
        servoPitch.write(PITCH_NEUTRAL + pCorr);
        servoRoll.write(ROLL_NEUTRAL + rCorr);
    }

    if (millis() - lastTelemetry > 50) {  // 20 Hz
        lastTelemetry = millis();
        Serial.printf("T %.2f %.2f\n", a.pitch, a.roll);
    }
}
