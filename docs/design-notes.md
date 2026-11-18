# Design notes

## Key decisions

| Decision | Choice | Reason |
|---|---|---|
| Arm DOF | 5 (yaw, shoulder, elbow, wrist pitch, wrist roll) | The mecanum base already moves in any direction, so a 6th joint adds cost and complexity for little gain |
| End effector | Flat platform/fork under the plate | A claw gripping a loaded plate is fragile and spills easily |
| Levelling | IMU on end effector, PID on wrist pitch & roll | Measures the plate's actual tilt, and the arm does the levelling, so no separate tray gimbal is needed |
| Big joints | NEMA 17 steppers + ~20:1 printed planetary/cycloidal gearboxes | Hobby servos can't supply the shoulder/elbow torque |
| Wrist joints | High-torque servos (≥ 2.5 N·m) | Low torque needed, compact, easy to drive |
| Compute | Pi (high level) + ESP32 (real-time) | Linux jitter is bad for control loops |

## Arm torque estimate (static, arm horizontal, worst case)

Assumptions (update these once the CAD exists):

| Item | Mass | Distance from shoulder |
|---|---|---|
| Plate (payload) | 1.0 kg | 0.40 m |
| Wrist + end effector | 0.3 kg | 0.40 m |
| Elbow motor + gearbox | 0.4 kg | 0.20 m |
| Forearm link | 0.2 kg | 0.30 m (centre) |
| Upper-arm link | 0.2 kg | 0.10 m (centre) |

**Shoulder:**
τ = g Σ m·r = 9.81 × (0.40 + 0.12 + 0.08 + 0.06 + 0.02) = 9.81 × 0.68 ≈ **6.7 N·m**

**Elbow** (distances measured from elbow, 0.2 m out):
τ = 9.81 × (1.0×0.2 + 0.3×0.2 + 0.2×0.1) = 9.81 × 0.28 ≈ **2.7 N·m**

**Wrist pitch** (plate centre ~0.1 m from wrist axis):
τ ≈ 9.81 × (1.0×0.1 + small) ≈ **1.2 N·m**

| Joint | Static | Design target (2× safety) |
|---|---|---|
| Shoulder | 6.7 N·m | **≥ 13 N·m** |
| Elbow | 2.7 N·m | **≥ 5.5 N·m** |
| Wrist pitch | 1.2 N·m | **≥ 2.5 N·m** |

For reference, an MG996R servo gives ~1 N·m and a DS3218 ~2 N·m. A NEMA 17 gives ~0.4 N·m holding,
so with a 20:1 gearbox at ~70 % efficiency it gives ~5.6 N·m. **The shoulder needs a larger motor
(NEMA 17 with a higher ratio, or NEMA 23), a counterbalance spring, or both.**

A shoulder gas spring or tension spring sized to cancel the arm's own weight can roughly halve
the shoulder torque.

## Tipping / stability

Arm extended with a plate: overturning moment ≈ 7 N·m (static) plus inertial loads from braking.

Static check: robot mass *M* with the tipping edge at half-width *w* from the centre of gravity:
need *M·g·w* > moment. With *w* = 0.2 m, *M* > 7 / (9.81 × 0.2) ≈ 3.6 kg (static only).
Braking and turning multiply this several times, so:

- Keep the battery and motors as low as possible in the base
- Base footprint ≥ 400 × 400 mm; target total mass ≥ 10 kg
- Mount the arm as low on the mast as the serving height allows
- Limit base acceleration in software, more strictly when the arm is extended

## Levelling PID

- Sensor: 6-axis IMU (e.g. MPU-6050 / ICM-42688 / BNO085) on the end effector
- Use a complementary filter (or the BNO085's on-chip fusion) for pitch and roll
- Two independent PID loops: pitch → wrist pitch servo, roll → wrist roll servo
- Loop rate: 200–500 Hz on the ESP32
- Start with P only, add D to damp oscillation, then a little I to remove steady tilt
- Feed-forward option: the base's commanded acceleration lets you pre-tilt before the
  disturbance arrives (stretch goal)

## Open questions

- [ ] Carry-and-level only, or full pick-and-place? (pick-and-place needs IK + better accuracy)
- [ ] Battery voltage: 12 V or 24 V system?
- [ ] Mast: fixed height or telescoping?
- [x] Navigation: black-tape line following + NFC-tagged nodes (see [system-plan.md](system-plan.md))
- [ ] Node identification: NFC tags or ArUco markers?
- [ ] Backend link: WebSocket or MQTT?
