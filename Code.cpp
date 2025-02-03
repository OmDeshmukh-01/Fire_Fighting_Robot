#include <Servo.h>
#include <AFMotor.h>

Servo myservo;
int pos = 0;

AF_DCMotor motor1(1);
AF_DCMotor motor2(2);
AF_DCMotor motor4(4);

boolean fire = false;

#define L_S A0  // Left sensor
#define F_S A2  // Front sensor
#define R_S A4  // Right sensor
#define BL_S A1 // Back-left sensor
#define BR_S A5   // Back-right sensor

void setup() {
  pinMode(L_S, INPUT);
  pinMode(F_S, INPUT);
  pinMode(R_S, INPUT);
  pinMode(BL_S, INPUT);
  pinMode(BR_S, INPUT);

  myservo.attach(10);
  myservo.write(90);
}

void put_off_fire() {
  delay(500);

  motor1.run(RELEASE);
  motor4.run(RELEASE);
  motor2.run(FORWARD);

  for (pos = 50; pos <= 130; pos += 1) {
    myservo.write(pos);
    delay(15);
  }

  for (pos = 130; pos >= 50; pos -= 1) {
    myservo.write(pos);
    delay(15);
  }

  motor2.run(RELEASE);
  myservo.write(90);

  fire = false;
}

void loop() {
  myservo.write(90);

  // If no fire detected by any sensor
  if (digitalRead(L_S) == 1 && digitalRead(F_S) == 1 && digitalRead(R_S) == 1 && digitalRead(BL_S) == 1 && digitalRead(BR_S) == 1) {
    motor1.setSpeed(240);
    motor2.setSpeed(240);
    motor4.setSpeed(240);

    motor1.run(RELEASE);
    motor2.run(RELEASE);
    motor4.run(RELEASE);
  }
  // Front sensor detects fire
  else if (digitalRead(F_S) == 0) {
    motor1.setSpeed(240);
    motor2.setSpeed(240);
    motor4.setSpeed(240);

    motor1.run(FORWARD);
    motor4.run(FORWARD);
    motor2.run(RELEASE);

    delay(300);

    fire = true;
  }
  // Right sensor detects fire
  else if (digitalRead(R_S) == 0) {
    motor1.setSpeed(240);
    motor2.setSpeed(240);
    motor4.setSpeed(240);

    motor1.run(BACKWARD);
    motor4.run(FORWARD);
    motor2.run(RELEASE);

    delay(300);

    fire = true;
  }
  // Left sensor detects fire
  else if (digitalRead(L_S) == 0) {
    motor1.setSpeed(240);
    motor2.setSpeed(240);
    motor4.setSpeed(240);

    motor1.run(FORWARD);
    motor4.run(BACKWARD);
    motor2.run(RELEASE);

    delay(300);

    fire = true;
  }
  // Back-left sensor detects fire
  else if (digitalRead(BL_S) == 0) {
    motor1.setSpeed(240);
    motor2.setSpeed(240);
    motor4.setSpeed(240);

    motor1.run(FORWARD);
    motor4.run(BACKWARD);
    motor2.run(RELEASE);

    delay(1000);

    fire = true;
  }
  // Back-right sensor detects fire
  else if (digitalRead(BR_S) == 0) {
    motor1.setSpeed(240);
    motor2.setSpeed(240);
    motor4.setSpeed(240);

    motor1.run(BACKWARD);
    motor4.run(FORWARD);
    motor2.run(RELEASE);

    delay(1000);

    fire = true;
  }

  delay(200);

  // Keep checking if there's still fire to put off
  while (fire == true) {
    put_off_fire();
  }
}