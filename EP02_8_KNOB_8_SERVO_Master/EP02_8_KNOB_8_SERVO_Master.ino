#include <SoftwareSerial.h>

#define SW_SERIAL_TX     2
#define SW_SERIAL_RX     3

SoftwareSerial BTSerial(SW_SERIAL_RX, SW_SERIAL_TX);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  BTSerial.begin(9600);
}

int tempADC = 0;
int adcPin[8] = {A0, A1, A2, A3, A4, A5, A6, A7};
byte angle = 0;
void loop() {
  // put your main code here, to run repeatedly:

  for (int id = 0; id < 8; id ++) {
    tempADC  = analogRead(adcPin[id]);
    tempADC  = min(842, tempADC);
    tempADC  = max(113, tempADC);
    angle = byte(map(tempADC, 113, 842, 0, 180));

    delay(5); // must .

    BTSerial.write(255);
    BTSerial.write(id);
    BTSerial.write(angle);
  }
}
