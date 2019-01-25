#include <SoftwareSerial.h>

#define SW_SERIAL_TX     A2 //will be connected with RX of HC-12
#define SW_SERIAL_RX     A3 // will be connected with TX of HC-12
#define HC12_SETUP  10  // connected with SET : LOW for AT Command

#define MULTI_01_S0 2
#define MULTI_01_S1 3
#define MULTI_01_S2 4
#define MULTI_01_S3 5
#define MULTI_01_ADC A0

#define MULTI_02_S0 6
#define MULTI_02_S1 7
#define MULTI_02_S2 8
#define MULTI_02_S3 9
#define MULTI_02_ADC A1


SoftwareSerial BTSerial(SW_SERIAL_RX, SW_SERIAL_TX);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  BTSerial.begin(9600);

  pinMode(MULTI_01_S0, OUTPUT);
  pinMode(MULTI_01_S1, OUTPUT);
  pinMode(MULTI_01_S2, OUTPUT);
  pinMode(MULTI_01_S3, OUTPUT);

  pinMode(MULTI_02_S0, OUTPUT);
  pinMode(MULTI_02_S1, OUTPUT);
  pinMode(MULTI_02_S2, OUTPUT);
  pinMode(MULTI_02_S3, OUTPUT);

}

int tempADC = 0;
int adcPin[8] = {A0, A1, A2, A3, A4, A5, A6, A7};
byte angle = 0;
void loop() {
  // put your main code here, to run repeatedly:

  while (1) {

    //for (byte id = 0 ; id < 32 ; id ++) {

for (byte id = 16 ; id < 32 ; id ++) {
      tempADC  = readADC(id);
      tempADC  = min(842, tempADC);
      tempADC  = max(113, tempADC);
      angle = byte(map(tempADC, 113, 842, 0, 180));

      //delay(5); // must .

      BTSerial.write(0xff);
      BTSerial.write(0xff);
      BTSerial.write(id);
      BTSerial.write(angle);
      //Serial.println(angle);
      BTSerial.write((byte)~(0xff + 0xff + id + angle));
      //Serial.println((byte)~(0xff + 0xff + id + angle));

    }

  }
}

int readADC(int sensorNumber) {

  if (sensorNumber < 16) {
    digitalWrite(MULTI_01_S0, sensorNumber & 0b00000001);
    digitalWrite(MULTI_01_S1, sensorNumber & 0b00000010);
    digitalWrite(MULTI_01_S2, sensorNumber & 0b00000100);
    digitalWrite(MULTI_01_S3, sensorNumber & 0b00001000);
    return analogRead(MULTI_01_ADC);
  } else {
    digitalWrite(MULTI_02_S0, (sensorNumber - 16) & 0b00000001);
    digitalWrite(MULTI_02_S1, (sensorNumber - 16) & 0b00000010);
    digitalWrite(MULTI_02_S2, (sensorNumber - 16) & 0b00000100);
    digitalWrite(MULTI_02_S3, (sensorNumber - 16) & 0b00001000);
    return analogRead(MULTI_02_ADC);
  }
}
