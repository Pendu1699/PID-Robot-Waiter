# Hardware / electronics

Wiring diagrams, schematics, and power distribution.

## Power plan (draft)

```
Battery ── Fuse ── Main switch ── E-STOP ──┬── Motor drivers (wheels)
                                           ├── Stepper drivers (arm)
                                           ├── Buck 6–7.4 V ── Wrist servos
                                           └── Buck 5 V ────── Raspberry Pi, ESP32
```

The E-stop must cut power to **all motors**. Common ground between all logic and power rails.
