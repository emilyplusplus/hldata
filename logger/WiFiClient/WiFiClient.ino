#include <Wire.h>
#include <ESP8266WiFi.h>
#include <stdio.h>

const char* ssid     = "Ariem Eowyn";
const char* password = "****";

void setup() {
  Wire.setClock(100000);
  Wire.setClockStretchLimit(40000);    // in µs
  Wire.begin();
  Serial.begin(115200);
  delay(10);

  // We start by connecting to a WiFi network

  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  int i = 0;
  char message[20];

  Wire.requestFrom(8,20);

  while (Wire.available()) {
    message[i] = (char)Wire.read();
    i++;
  }

  Serial.println(message);

  char temp[10] = {0,0,0,0,0,0,0,0,0,0};
  char lux[10] = {0,0,0,0,0,0,0,0,0,0};

  char *found;

  found = strchr(message, ',');
  strncpy(temp,message,found-message);
  strcpy(lux,found+1);
  
  Serial.println(found-message);
  Serial.println(temp);
  Serial.println(lux);

  float t = atof(temp);
  float l = atof(lux);

  Serial.println(t);
  Serial.println(l);
  
  // Use WiFiClient class to create TCP connections
  WiFiClient client;
  const int httpPort = 8080;
  if (!client.connect("10.0.0.2", httpPort)) {
    Serial.println("connection failed");
    return;
  }
  
  // We now create a URI for the request
  String url = "/record";
  
  Serial.print("Requesting URL: ");
  Serial.println(url);
  
  // This will send the request to the server
  client.print(String("POST /record HTTP/1.1\r\n") +
               "Host: 10.0.0.2:8080\r\n" + 
               "Cache-Control: no-cache\r\n" + 
                "Content-Length: " + (9 + strlen(temp) + 8 + strlen(lux) + 1) + "\r\n"+
                "Accept: */*\r\n"+
               "Content-Type: application/json\r\n\r\n" +
               "{\"temp\": " + (t) + ",\"lux\": " + (l) + "}\r\n");
  unsigned long timeout = millis();
  while (client.available() == 0) {
    if (millis() - timeout > 5000) {
      Serial.println(">>> Client Timeout !");
      client.stop();
      return;
    }
  }
  
  // Read all the lines of the reply from server and print them to Serial
  while(client.available()){
    String line = client.readStringUntil('\r');
    Serial.print(line);
  }
  
  Serial.println();
  Serial.println("closing connection");
  
  delay(30*1000);
}

