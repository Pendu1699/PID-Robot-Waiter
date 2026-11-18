# Parts list (draft)

Prices aren't listed yet. Check current AU suppliers (Core Electronics, Jaycar, Altronics,
AliExpress) and fill in as you buy.

## Compute & sensing

| Qty | Part | Notes |
|---|---|---|
| 1 | Raspberry Pi 4 (8 GB) ✅ owned | High-level control, route planning, ML inference |
| 1 | ESP32 dev board | Real-time PID, motors, joints |
| 1 | IMU (BNO085 or MPU-6050) | On end effector. BNO085 has onboard sensor fusion |
| 1 | Pi Camera Module 3 | Plate detection, ArUco markers, obstacle detection |
| 1 | *(optional)* AI accelerator HAT | Faster YOLO inference |

## Drive base

| Qty | Part | Notes |
|---|---|---|
| 4 | Mecanum wheels (~80–100 mm) | 2× left-hand, 2× right-hand rollers |
| 4 | DC gear motors **with encoders** (e.g. JGB37-520) | Encoders needed for wheel speed PID |
| 2 | Dual motor drivers (e.g. TB6612FNG or BTS7960 for higher current) | Size for motor stall current |
| 1 | Base chassis plate (aluminium / plywood) | ≥ 400 × 400 mm |
| 1 | IR reflectance sensor array (e.g. QTR-8RC) | Line following, mounted under the front of the base |
| 1 | NFC/RFID reader (e.g. PN532) | Reads node tags under the base |
| ~20 | NFC sticker tags (NTAG213) | One per junction / table / pickup station |
| — | Black gaffer / painter's tape (removable) | Tape path. Get permission for the venue first |

## Arm

| Qty | Part | Notes |
|---|---|---|
| 3 | NEMA 17 steppers (or NEMA 23 for shoulder) | Base yaw, shoulder, elbow |
| 3 | Stepper drivers (TMC2209) | Quiet, current-limited |
| 3 | Gearboxes, 3D printed planetary / cycloidal | ~20:1 or more, see design notes |
| 2 | High-torque servos (≥ 25 kg·cm, e.g. DS3225) | Wrist pitch & roll |
| 3 | Limit switches | Joint homing |
| 1 | Shoulder counterbalance spring | Halves shoulder torque |
| — | Bearings (608, thin-section for joints), M3/M4/M5 hardware | |

## Structure

| Qty | Part | Notes |
|---|---|---|
| 1 | Aluminium extrusion (2040 / 4040) for mast | ~600–700 mm |
| — | 3D-printed brackets, PETG or ABS | Avoid PLA near motors (heat) |

## Venue / app

| Qty | Part | Notes |
|---|---|---|
| 1 | Wi-Fi router or phone hotspot | eduroam usually blocks device-to-device traffic |
| — | Printed table QR codes + ArUco markers | Table ordering + pickup station pose |
| 1 | Pickup shelf at fixed height | Known position for the arm |

## Power & safety

| Qty | Part | Notes |
|---|---|---|
| 1 | Battery (e.g. 4S LiPo/Li-ion pack or 12 V LiFePO4) | Decide 12 V vs 24 V system |
| 1 | BMS / battery protection | |
| 1 | Buck converter 5 V ≥ 5 A | For Pi |
| 1 | Buck converter 6–7.4 V | For servos |
| 1 | **Emergency stop button** (latching, cuts motor power) | Required |
| 1 | Main fuse + switch | |
