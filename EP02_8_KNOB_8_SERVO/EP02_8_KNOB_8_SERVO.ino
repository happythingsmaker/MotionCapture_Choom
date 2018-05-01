#include <Adafruit_PWMServoDriver.h>
Adafruit_PWMServoDriver pwmDriver = Adafruit_PWMServoDriver(0x40);

void setup() {
  // put your setup code here, to run once:
  pwmDriver.begin();
  pwmDriver.setPWMFreq(51); // 50 Hz (needs to add 1)
}

int tempPotentiometerValue = 0;
int adcPin[8] = {A0, A1, A2, A3, A4, A5, A6, A7};
int pwmRisingTime = 0;
int pwmFallingTime = 0;

void loop() {
  // put your main code here, to run repeatedly:
  for (int id = 0; id < 8; id ++) {
    tempPotentiometerValue = analogRead(adcPin[id]);
    pwmFallingTime = map(tempPotentiometerValue, 113, 842, 102, 512);
    pwmDriver.setPWM(id, pwmRisingTime, pwmFallingTime);
  }
}



