#include <Wire.h>

char message[20];

void setup() {
  Serial.begin(115200);
  
  Wire.onRequest(request); 
  Wire.begin(8);
}

void loop() {
  for(int i = 0; i < 20; i++) {
    message[i] = 0;
  }
  
  float temp = analogRead(A3)/1024.0*5000/10;
  float lux = analogRead(A2)/1024.0*5000;

  String _message = String(temp) + "," + String(lux);
  _message.toCharArray(message, 20);

  Serial.println(message);
  
  delay(1000);
}

void request() {
  Wire.write(message,20);
}
