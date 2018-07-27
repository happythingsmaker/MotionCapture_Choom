// video instruction : https://youtu.be/gxPXpow3xNk
// YouTube Channel : Eunchan Park
// This code receives Address(PWM board), Motor ID (0~16) and Angle(0~180)
// in order to verify data, add checksum byte like Robotis

#include <Adafruit_PWMServoDriver.h>
#include <SoftwareSerial.h>

// we need one more serial Communication for HC-12
#define SW_SERIAL_TX     2
#define SW_SERIAL_RX     3
SoftwareSerial BTSerial(SW_SERIAL_RX, SW_SERIAL_TX);

// The 0x40 board is for upper body motors
Adafruit_PWMServoDriver pwmDriver_0 = Adafruit_PWMServoDriver(0x40 + 0);

// This 0x41 board is for legs motors
Adafruit_PWMServoDriver pwmDriver_1 = Adafruit_PWMServoDriver(0x40 + 1);


void setup() {
  // begin serial communications
  Serial.begin(9600);
  BTSerial.begin(9600);

  // begin and setup the PWM boards
  pwmDriver_0.begin();
  pwmDriver_0.setPWMFreq(51);

  pwmDriver_1.begin();
  pwmDriver_1.setPWMFreq(51);

  // have all the motors go center angle.
  // If you want to understand "setPWM" function,
  // please refer to https://www.adafruit.com/product/815

  for (int i = 0 ; i < 16; i ++) {
    pwmDriver_0.setPWM(i, 0,  map(90, 0, 180, 111, 491));
    pwmDriver_1.setPWM(i, 0,  map(90, 0, 180, 111, 491));
  }
  //544/20000 * 4096 = 111.4112
  //2400/20000 * 4096 = 491.52
}

const uint8_t dataLength = 3; //board ID, motor ID, angle, checkSum
uint8_t dataPacket[dataLength] = {0};
uint8_t motorID = 0;
uint8_t motorAngle = 0;
uint8_t revCheckSum = 0;

void loop() {
  
  while (BTSerial.available() >= 6) {
    // we will receive data from Master robot in these sequence
    // 0xff 0xff motorID motorAngle checkSum(calculated from master robot)
    // the way to calculating checksum is ~(0xff + 0xff + motorID + motorAngle)
    // in order to read data successfully, we need checksum.
    // and we will check whether the first 2 data are 0xff
    // 0xff 0xff is some kind of starting packet
   
    if (BTSerial.read() != 0xff) {
      continue;
    }
    if (BTSerial.read() != 0xff) {
      continue;
    }

    // now, we receive real information
    motorID = BTSerial.read();
    motorAngle = BTSerial.read();

    // this data is calculated from mater robot.
    revCheckSum = BTSerial.read();

    // we calculate checksum in this slave robot.
    if (checkSum() != revCheckSum) {
      continue;
    }

    // so far, data from master robot seems good.
    // we can move this robot by using the data.

    if (motorID  < 16) {
      pwmDriver_0.setPWM(motorID, 0,  map(motorAngle, 0, 180, 111, 491));
    } else {
      pwmDriver_1.setPWM(motorID - 16, 0,  map(motorAngle, 0, 180, 111, 491));
    }    
  }

}

uint8_t checkSum() {
  uint8_t result = 0;
  result += 0xff;
  result += 0xff;
  result += motorID;
  result += motorAngle; 
  return ~result;
}
