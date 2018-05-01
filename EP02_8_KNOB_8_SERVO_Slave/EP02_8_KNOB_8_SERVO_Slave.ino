#include <Adafruit_PWMServoDriver.h>
#include <SoftwareSerial.h>

#define SW_SERIAL_TX     2
#define SW_SERIAL_RX     3

Adafruit_PWMServoDriver pwmDriver = Adafruit_PWMServoDriver(0x40);
SoftwareSerial BTSerial(SW_SERIAL_RX, SW_SERIAL_TX);


void setup() {
  // put your setup code here, to run once:
  BTSerial.begin(9600);

  pwmDriver.begin();
  pwmDriver.setPWMFreq(51);
  pwmDriver.setPWM(0, 0, 500);  // setPWM(ID, on Time, off Time out of 4096)
  //544/20000 * 4096 = 111.4112
  //2400/20000 * 4096 = 491.52
}

byte tempID = 0;
byte tempAngle = 0;
void loop() {
  // put your main code here, to run repeatedly:

  while (BTSerial.available() > 3) {
    if (BTSerial.read() == 255) {
      tempID = BTSerial.read();
      tempAngle = BTSerial.read();
      pwmDriver.setPWM(tempID, 0, map(tempAngle, 0, 180, 111, 491));
    }
  }
}
