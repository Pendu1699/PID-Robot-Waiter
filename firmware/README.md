# Firmware (ESP32)

Built with [PlatformIO](https://platformio.org/) (VS Code extension).

From the repository root:

```sh
cd firmware
pio run               # build without flashing
pio run -t upload     # build + flash
pio device monitor    # serial monitor at 115200
```

## Current state

`src/main.cpp` is the **levelling bench test**. It targets a 250 Hz loop for the wrist pitch and roll servos.
The IMU stub returns zero on both axes. Fit and implement the sensor before tuning gains against actual tilt.

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
