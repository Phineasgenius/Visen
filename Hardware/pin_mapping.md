# Visen — Pin Mapping Reference

| Component | Pin | GPIO |
|-----------|-----|------|
| HC-SR04 TRIG | TRIG | GPIO 26 |
| HC-SR04 ECHO | ECHO | GPIO 25 |
| Buzzer | BUZZ | GPIO 33 |
| Mode Button | BTN | GPIO 0 |
| Servo Motor | SERVO_PIN | GPIO 27 |

## Notes
- Button uses internal pull-up resistor (INPUT_PULLUP)
- Servo is driven using manual PWM pulse (no library required)
- Buzzer uses Arduino `tone()` function
- HC-SR04 operates at 3.3V–5V; use a level shifter if needed
