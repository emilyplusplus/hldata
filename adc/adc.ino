#include <Wire.h>

void setup() {
  Serial.begin(115200);
  Wire.begin();
}

void loop() {
  float temp = analogRead(A3)/1024.0*5000/10;
  float lux = analogRead(A2)/1024.0*5000;

  char message[20];
  String _message = String(temp) + "," + String(lux);
  _message.toCharArray(message, 20);

  Serial.println(message);

  Wire.beginTransmission(8);
  Wire.write(message,20);
  Wire.endTransmission();

  delay(1*10*1000);
}
