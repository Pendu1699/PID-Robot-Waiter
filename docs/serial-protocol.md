# Serial protocol: Pi ↔ ESP32 (draft)

Plain-text, newline-terminated ASCII so it's easy to debug from a serial monitor.
115200 baud to start, increase later if needed.

## Current bench firmware

The ESP32 accepts `L` and `K` and ignores the other commands below. It sends
`T pitch roll` about 20 times per second. Both values are in degrees and read
zero with the current IMU stub. `L 0` pauses PID updates and leaves the servos
at their last commanded positions.

## Planned command set (Pi → ESP32)

| Command | Meaning | Example |
|---|---|---|
| `V vx vy wz` | Base velocity (m/s, m/s, rad/s) | `V 0.20 0.00 0.0` |
| `J j1 j2 j3 j4 j5` | Arm joint targets (degrees) | `J 0 45 -30 0 0` |
| `L 0/1` | Levelling off/on | `L 1` |
| `K axis kp ki kd` | Set PID gains live (`P`=pitch, `R`=roll) | `K P 2.0 0.1 0.05` |
| `H` | Home arm joints | `H` |
| `S` | Stop everything | `S` |

## Planned telemetry format (ESP32 → Pi)

```
T pitch roll j1 j2 j3 j4 j5 battV
```
Example: `T 0.4 -0.2 0 45 -30 1.2 0.3 15.8`

## Planned stop behaviour

- The drive firmware must stop the base if no command arrives for 250 ms (watchdog)
- The `S` command and the hardware E-stop must take priority over motion commands
