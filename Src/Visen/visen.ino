// ESP32 Dual Mode: Obstacle Detector + Water Level Monitor
// With Bluetooth capabilities
#include <BluetoothSerial.h>

#define TRIG 26
#define ECHO 25
#define BUZZ 33
#define BTN 0
#define SERVO_PIN 27

#define MODE_OBSTACLE 0
#define MODE_WATER 1

int mode = MODE_OBSTACLE;
bool enabled = true;
unsigned long lastPress = 0;
unsigned long lastWarningBeep = 0;

BluetoothSerial SerialBT;

void servoWrite(int angle) {
  int pulseWidth = map(angle, 0, 180, 500, 2500);
  digitalWrite(SERVO_PIN, HIGH);
  delayMicroseconds(pulseWidth);
  digitalWrite(SERVO_PIN, LOW);
  delay(15);
}

void setup() {
  Serial.begin(115200);
  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);
  pinMode(BTN, INPUT_PULLUP);
  pinMode(BUZZ, OUTPUT);
  pinMode(SERVO_PIN, OUTPUT);
  servoWrite(0);
  SerialBT.begin("ESP32_Assist_Device");
  Serial.println("Bluetooth Started: ESP32_Assist_Device");
  for(int i = 0; i < 3; i++) {
    tone(BUZZ, 800 + i*400);
    delay(100);
    noTone(BUZZ);
    delay(50);
  }
}

void loop() {
  if(digitalRead(BTN) == LOW && millis() - lastPress > 500) {
    lastPress = millis();
    delay(50);
    unsigned long pressStart = millis();
    while(digitalRead(BTN) == LOW && millis() - pressStart < 1000) delay(10);
    if(millis() - pressStart < 1000) {
      enabled = !enabled;
      tone(BUZZ, enabled ? 1500 : 1000);
      delay(100);
      noTone(BUZZ);
      SerialBT.println(enabled ? "Device ON" : "Device OFF");
    } else {
      mode = (mode == MODE_OBSTACLE) ? MODE_WATER : MODE_OBSTACLE;
      playModeBeep();
      SerialBT.println(mode == MODE_OBSTACLE ? "Mode: Obstacle Detection" : "Mode: Water Level");
    }
    delay(300);
  }

  if(!enabled) { noTone(BUZZ); delay(100); return; }

  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);

  long dur = pulseIn(ECHO, HIGH, 30000);
  if(dur == 0) { noTone(BUZZ); return; }

  int d = dur * 0.034 / 2;
  SerialBT.print("Distance: ");
  SerialBT.print(d);
  SerialBT.println(" cm");

  if(mode == MODE_OBSTACLE) obstacleMode(d);
  else waterLevelMode(d);

  delay(60);
}

void obstacleMode(int d) {
  if(d < 30) { SerialBT.println("ALERT: Very Close!"); tone(BUZZ, 2500); }
  else if(d < 100) { SerialBT.println("WARNING: Close"); tone(BUZZ, map(d,30,100,2000,1000)); delay(50); noTone(BUZZ); delay(map(d,30,100,50,200)); }
  else if(d < 200) { SerialBT.println("CAUTION: Medium"); tone(BUZZ, map(d,100,200,1000,500)); delay(100); noTone(BUZZ); delay(map(d,100,200,200,400)); }
  else if(d < 300) { SerialBT.println("INFO: Far"); tone(BUZZ, map(d,200,300,500,300)); delay(100); noTone(BUZZ); delay(map(d,200,300,400,800)); }
  else noTone(BUZZ);
}

void waterLevelMode(int d) {
  if(d < 50) {
    SerialBT.println("WATER LEVEL: CRITICAL (>50cm high)");
    tone(BUZZ, 2200);
    static unsigned long lastMove = 0;
    static bool servoDirection = true;
    if(millis() - lastMove > 500) { servoWrite(servoDirection ? 180 : 0); servoDirection = !servoDirection; lastMove = millis(); }
  } else if(d >= 50 && d <= 100) {
    SerialBT.println("WATER LEVEL: WARNING (50-100cm)");
    if(millis() - lastWarningBeep > 180000 || lastWarningBeep == 0) { tone(BUZZ, 1500); delay(500); noTone(BUZZ); lastWarningBeep = millis(); }
    else noTone(BUZZ);
    servoWrite(90);
  } else {
    SerialBT.println("WATER LEVEL: SAFE (>100cm)");
    noTone(BUZZ);
    servoWrite(0);
    lastWarningBeep = 0;
  }
}

void playModeBeep() {
  if(mode == MODE_OBSTACLE) {
    for(int i = 0; i < 2; i++) { tone(BUZZ, 2000); delay(100); noTone(BUZZ); delay(100); }
  } else {
    for(int i = 0; i < 3; i++) { tone(BUZZ, 800); delay(150); noTone(BUZZ); delay(100); }
  }
}
