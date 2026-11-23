# Raspberry Pi code

The [serial client](waiter/serial_link.py) prints telemetry from the ESP32. From the
repository root on the Pi, connect the ESP32 over USB and run:

```sh
cd pi
python3 -m venv .venv
. .venv/bin/activate
python -m pip install -r requirements.txt
python -m waiter.serial_link /dev/ttyUSB0
```

Use the serial port assigned to your board. The current firmware sends pitch and roll
in degrees. See the [serial protocol](../docs/serial-protocol.md) for supported commands.

Navigation and arm kinematics are planned. The ordering UI is described in the
[system plan](../docs/system-plan.md).
