#include <Bridge.h>
#include <HttpClient.h>

const int transistorPin = 9;    // connected to the base of the transistor
const int sensorPing = 0; // moisture sensor
const int pumpValueHIGH = 50;
const int pumpValueLOW = 0;



void setup() {
  Serial.begin(57600);
  Serial.println("*** SETUP");
  // set  the transistor pin as output:
  pinMode(transistorPin, OUTPUT);
  Bridge.begin();
  while(!Serial);


}

boolean activatePump (int humidity) {
  if (humidity > 300 ) {
    return true;
  } else {
    return false;
  }
}

void loop() {
// Initialize the client library
  HttpClient client;

  // Make a HTTP request:
  client.get("http://www.arduino.cc/asciilogo.txt");

  // if there are incoming bytes available
  // from the server, read them and print them:
  while (client.available()) {
    char c = client.read();
    Serial.print(c);
  }
  Serial.flush();

  delay(5000);
}

