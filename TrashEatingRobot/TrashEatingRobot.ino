#include <Servo.h>

Servo armServo;

void setup() {
  armServo.attach(12);
  armServo.write(90);

  pinMode(A7, INPUT)  ;
  pinMode(13, OUTPUT);
  pinMode(0, OUTPUT);
  pinMode(1, OUTPUT);
}

int sensorValue = 0;
int prevSensorValue = 0;
const int THRESHOLD = 360;
void loop() {
  
  sensorValue = analogRead(A7);
  if (prevSensorValue <= THRESHOLD) {
    if (sensorValue > THRESHOLD) {
      action();
    }
  }
  
  prevSensorValue = sensorValue;
  delay(10);
}

void action() {
  led(true);

  //eating
  delay(1000);
  armServo.attach(12);
  armServo.write(10);
  delay(300);
  armServo.write(70);
  delay(500);

  //after ate
  delay(100);
  armServo.write(50);
  delay(250);
  armServo.write(70);
  delay(250);
  armServo.write(50);
  delay(250);
  armServo.write(70);
  delay(250);
  armServo.write(50);
  delay(250);
  armServo.write(70);
  delay(250);
  armServo.write(50);
  delay(250);
  armServo.write(90);
  delay(250);

  //release arm's torque
  armServo.detach();
  led(false);
}

void led(bool onOff) {
  if (onOff) {
    digitalWrite(13, HIGH);
    digitalWrite(0, LOW);
    digitalWrite(1, LOW);
  } else {
    digitalWrite(13, LOW);
    digitalWrite(0, HIGH);
    digitalWrite(1, HIGH);
  }
}

