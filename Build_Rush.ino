// ==================== PIN DEFINITIONS ====================
#define PWMA    25    // Left motor PWM
#define AIN1    26
#define AIN2    27
#define PWMB    14    // Right motor PWM
#define BIN1    12
#define BIN2    13
#define STBY    33

#define PWM_FREQ  20000
#define PWM_RES   8     // 0-255

int testSpeed = 180;      // Speed (0-255)
int delayTime = 2000;     // Duration of each test (ms)

void setup() {
  Serial.begin(115200);
  delay(1000);
  Serial.println("\n=== Motor Test Starting ===");

  // Direction pins
  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);
  pinMode(BIN1, OUTPUT);
  pinMode(BIN2, OUTPUT);
  pinMode(STBY, OUTPUT);
  digitalWrite(STBY, HIGH);   // Enable TB6612

  // ===== New ESP32 Core 3.x PWM setup =====
  ledcAttach(PWMA, PWM_FREQ, PWM_RES);
  ledcAttach(PWMB, PWM_FREQ, PWM_RES);

  stopMotors();
}

void loop() {
  // 1. Left motor Forward
  Serial.println("Left motor → FORWARD");
  setMotor(PWMA, AIN1, AIN2, testSpeed);
  setMotor(PWMB, BIN1, BIN2, 0);
  delay(delayTime);
  stopMotors();
  delay(800);

  // 2. Left motor Reverse
  Serial.println("Left motor → REVERSE");
  setMotor(PWMA, AIN1, AIN2, -testSpeed);
  setMotor(PWMB, BIN1, BIN2, 0);
  delay(delayTime);
  stopMotors();
  delay(800);

  // 3. Right motor Forward
  Serial.println("Right motor → FORWARD");
  setMotor(PWMA, AIN1, AIN2, 0);
  setMotor(PWMB, BIN1, BIN2, testSpeed);
  delay(delayTime);
  stopMotors();
  delay(800);

  // 4. Right motor Reverse
  Serial.println("Right motor → REVERSE");
  setMotor(PWMA, AIN1, AIN2, 0);
  setMotor(PWMB, BIN1, BIN2, -testSpeed);
  delay(delayTime);
  stopMotors();
  delay(800);

  // 5. Both Forward
  Serial.println("BOTH motors → FORWARD");
  setMotor(PWMA, AIN1, AIN2, testSpeed);
  setMotor(PWMB, BIN1, BIN2, testSpeed);
  delay(delayTime);
  stopMotors();
  delay(800);

  // 6. Both Reverse
  Serial.println("BOTH motors → REVERSE");
  setMotor(PWMA, AIN1, AIN2, -testSpeed);
  setMotor(PWMB, BIN1, BIN2, -testSpeed);
  delay(delayTime);
  stopMotors();
  delay(1500);

  Serial.println("----- Test cycle finished -----\n");
}

// ==================== Helper Functions ====================
void setMotor(int pwmPin, int in1, int in2, int speed) {
  if (speed > 0) {
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    ledcWrite(pwmPin, speed);
  } 
  else if (speed < 0) {
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    ledcWrite(pwmPin, -speed);
  } 
  else {
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
    ledcWrite(pwmPin, 0);
  }
}

void stopMotors() {
  setMotor(PWMA, AIN1, AIN2, 0);
  setMotor(PWMB, BIN1, BIN2, 0);
}
