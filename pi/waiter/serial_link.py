"""Serial link between the Raspberry Pi and the ESP32.

Protocol: docs/serial-protocol.md
"""
import sys
import serial


class SerialLink:
    def __init__(self, port: str, baud: int = 115200):
        self.ser = serial.Serial(port, baud, timeout=0.1)

    def send(self, line: str) -> None:
        self.ser.write((line.strip() + "\n").encode("ascii"))

    def drive(self, vx: float, vy: float, wz: float) -> None:
        self.send(f"V {vx:.3f} {vy:.3f} {wz:.3f}")

    def set_gains(self, axis: str, kp: float, ki: float, kd: float) -> None:
        self.send(f"K {axis} {kp} {ki} {kd}")

    def levelling(self, on: bool) -> None:
        self.send(f"L {int(on)}")

    def stop(self) -> None:
        self.send("S")

    def read_telemetry(self):
        """Return a list of floats from the next 'T ...' line, or None."""
        raw = self.ser.readline().decode("ascii", errors="ignore").strip()
        if raw.startswith("T "):
            try:
                return [float(x) for x in raw.split()[1:]]
            except ValueError:
                return None
        return None


if __name__ == "__main__":
    link = SerialLink(sys.argv[1] if len(sys.argv) > 1 else "/dev/ttyUSB0")
    while True:
        t = link.read_telemetry()
        if t:
            print(t)
