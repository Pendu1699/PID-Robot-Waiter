# Firmware (ESP32)

Built with [PlatformIO](https://platformio.org/) (VS Code extension).

```
pio run -t upload     # build + flash
pio device monitor    # serial monitor at 115200
```

## Current state

`src/main.cpp` is the **levelling bench test** (roadmap step 2): IMU, two PID loops and
the wrist pitch/roll servos. The IMU read is a placeholder for now.

## Tuning the levelling PID

Send gains live over serial (no reflashing):

```
K P 1.5 0 0       # pitch: P only
K P 1.5 0 0.05    # add D if it oscillates
K P 1.5 0.2 0.05  # add a little I if it settles slightly tilted
```

1. Set I and D to 0 and raise P until the plate oscillates, then back off about 30 %
2. Add D to damp overshoot
3. Add small I to remove steady-state tilt
