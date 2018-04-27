// http://Youtube.com/EunchanPark
// from one knob to one servo
#include <Servo.h>

Servo servo;

void setup() {
  servo.attach(9);
  Serial.begin(9600);
}

void loop() {
  int knobValue = analogRead(A0);
  int angle = map(knobValue , 113, 842 , 0, 180);
  servo.write(angle);
  Serial.println(knobValue);
  delay(10);
}
