# Raspberry Pi code

High-level control: UI, navigation, arm kinematics, and the serial link to the ESP32.

```
pip install -r requirements.txt
python -m waiter.serial_link /dev/ttyUSB0   # prints ESP32 telemetry
```

Planned modules:

- `waiter/serial_link.py`: talks to the ESP32 (see `docs/serial-protocol.md`)
- `waiter/kinematics.py`: arm forward/inverse kinematics
- `waiter/ui/`: web or phone control page
