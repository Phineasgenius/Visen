# Visen
### See Beyond Your Reach

> A compact, palm-sized multipurpose assistive device built on the ESP32 — designed primarily for the visually impaired as a smarter, longer-range alternative to the traditional cane.

---

## Overview

Visen is a handheld ESP32-based device roughly the size of a classic Nokia feature phone. It uses ultrasonic sensing to detect obstacles up to 4 meters away — double the range of a standard white cane — and delivers real-time audio feedback through intuitive buzzer patterns. Beyond navigation assistance, it serves two additional practical roles: a car parking sensor and a water tank level monitor.

#  Key Features

- 4-meter ultrasonic detection — far beyond the ~2m range of a traditional cane
- Intuitive audio alerts — buzzer frequency and pattern vary dynamically with distance
- 3 operating modes — switchable with a single button
- Bluetooth streaming — live sensor data sent to any paired device
- Servo level indicator — visual feedback for water tank monitoring
- Compact & portable — handheld, lightweight, fits in your palm

---

## Modes

### Mode 1 — Obstacle Detection (Primary)
Designed for visually impaired users as a cane replacement. Continuously measures distance and alerts via buzzer:

| Distance | Alert |
|----------|-------|
| < 30 cm | Continuous high-pitched tone (2500 Hz) |
| 30–100 cm | Fast intermittent beep |
| 100–200 cm | Slower intermittent beep |
| 200–300 cm | Slow low-frequency beep |
| > 300 cm | Silent |

---

### Mode 2 — Car Parking Sensor
Acts as a backup proximity sensor when your vehicle's reverse camera or parking sensors are unavailable or damaged. Uses the same distance-based buzzer logic as obstacle mode.

---

### Mode 3 — Water Tank Level Monitor
Monitors water level in overhead or underground tanks with tiered alerts:

| Level | Distance Reading | Alert |
|-------|-----------------|-------|
| Critical (nearly full) | < 50 cm | Continuous urgent buzz + servo oscillates |
| Warning (medium) | 50–100 cm | Single beep every 3 minutes |
| Safe (low/empty) | > 100 cm | Silent, servo at 0° |

---

## Button Controls

| Action | Result |
|--------|--------|
| Short press | Toggle device ON / OFF |
| Long press (1s+) | Switch between modes |

---

## Bluetooth

Visen streams live data to any paired Bluetooth device under the name `ESP32_Assist_Device`. No custom app needed — any serial Bluetooth terminal works.

Data streamed includes:
- Real-time distance in cm
- Mode-specific alerts (e.g. `ALERT: Very Close!`, `WATER LEVEL: CRITICAL`)

---

## Hardware Requirements

| Component | Pin |
|-----------|-----|
| Ultrasonic Sensor (HC-SR04) TRIG | GPIO 26 |
| Ultrasonic Sensor (HC-SR04) ECHO | GPIO 25 |
| Buzzer | GPIO 33 |
| Mode Button | GPIO 0 |
| Servo Motor | GPIO 27 |

---

## Dependencies

- [BluetoothSerial](https://github.com/espressif/arduino-esp32) — included in the ESP32 Arduino core
- Arduino IDE with ESP32 board support installed

To install ESP32 board support:
1. Open Arduino IDE → File > Preferences
2. Add to Additional Board Manager URLs: `https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json`
3. Go to Tools > Board > Board Manager, search `esp32`, and install

---

## Getting Started

1. Clone: `git clone https://github.com/yourusername/visen.git && cd visen`
2. Open `src/visen/visen.ino` in Arduino IDE
3. Select Board: Tools → Board → ESP32 Arduino → ESP32 Dev Module
4. Upload and pair with `ESP32_Assist_Device` via Bluetooth

---

## File Structure

```
visen/
├── src/
│   └── visen/
│       └── visen.ino          # Main Arduino sketch
├── docs/
│   ├── circuit_diagram.png    # Wiring schematic
│   └── demo.mp4               # Demo video (optional)
├── hardware/
│   └── pin_mapping.md         # Detailed pin reference
├── .gitignore
├── LICENSE
└── README.md
```

---

## Future Improvements

- [ ] Custom Android/iOS app with visual distance display
- [ ] Vibration motor for silent haptic feedback
- [ ] GPS integration for location tracking
- [ ] Rechargeable Li-Po battery with USB-C charging
- [ ] Voice announcements via small speaker module
- [ ] Waterproof enclosure for outdoor use

---

## Author

[@Phineasgenius](https://github.com/Phineasgenius)

---

## License

This project is licensed under the MIT License — see the [LICENSE](LICENSE) file for details.

---

Built with purpose. Designed for independence.
