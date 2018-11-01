// Welcome to the source code of "Hungry Robot"

// YouTube Instruction
// 3d printer version: https://youtu.be/KfP_LfUiwdc
// paper version: https://youtu.be/3qnU8uD0utM

// Documentation
// https://sites.google.com/view/100happythings/18-Hungry-Robot

// Select Arduino nano / ATmega328P (Old Bootloader)

// in order to use servo motor, we need to include a library file
#include <Servo.h>

// let's make an instance of Servo
Servo armServo;

// this function automatically runs only once when the Arduino's power up
void setup() {

  // we use pin number 12 for control the robot.
  armServo.attach(12);
  // move the motor to default angle
  armServo.write(90);

  // pin A7 is for the distance sensor
  pinMode(A7, INPUT);

  // these 3 pins (pin0, pin1, pin13) are for turning on LEDs
  // Arduino nano already has 3 LEDs on these pins.
  pinMode(13, OUTPUT);
  pinMode(0, OUTPUT);
  pinMode(1, OUTPUT);
}

// in order to check coming hand,
// we will keep the sensor value these variables
int sensorValue = 0;
int prevSensorValue = 0;

// When the sensor value is hight than the THRESHOLD value,
// The code will call action();
const int THRESHOLD = 360;

void loop() {

  // read A7's analog value and asign the value into sensorValue
  sensorValue = analogRead(A7);

  // these two lines means that some object has come
  // from outside of Threshold to inside of it.
  if (prevSensorValue <= THRESHOLD) {
    if (sensorValue > THRESHOLD) {
      // It's time to action
      action();
    }
  }

  // regardless the action, save current sensor value prevSensorValue
  // so that we can check the direction
  prevSensorValue = sensorValue;

  // this delay controls how often this loop is running
  // without this delay, this loop runs too fast
  // then, the differences between previous and current sensor value
  // can not be meaningful.
  delay(10);
}


void action() {
  // call this function for turning on three LEDs all together
  led(true);

  // eating sequence
  // wait 1000ms (1 second)
  delay(1000);

  // let's use pin12 for motor control
  armServo.attach(12);
  // let's move the motor to degree '10' (move the arm up)
  armServo.write(10);

  // wait 300 ms
  delay(300);

  // let's move the motor to degree '70' (move the arm down)
  armServo.write(70);
  delay(500);

  // after ate
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

  // release arm's torque
  armServo.detach();

  // call this function for turning off three LEDs all together
  led(false);
}

void led(bool onOff) {
  // pin 13's LED turns on when it is high
  // pin 0, 1's LED turn on when it is low
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

