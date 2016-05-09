/*
 # Example code for the moisture sensor
 # Editor : Lauren
 # Date : 13.01.2012
 # Version : 1.0
 # Connect the sensor to the A0 (Analog 0) pin on the Arduino board

 # the sensor value description
 # 0 ~300 dry soil
 # 300~700 humid soil
 # 700~950 in water
*/

#include <Bridge.h>
#include <HttpClient.h>

const int outPin = 9;
const int pumpLOW = 0;
const int pumpHIGH = 30;

const int LEDPIN=13;

void setup() {
  Serial.begin(57600);
  pinMode(outPin, OUTPUT);
  pinMode(LEDPIN, OUTPUT);
  Bridge.begin();
}
void onAndOff() {
  analogWrite(outPin, pumpLOW);
  delay(1000);
  analogWrite(outPin, pumpHIGH);
  delay(1000);
}

void twoSecondsPump(){
  waterRequest(true);
  analogWrite(outPin, pumpHIGH);
  delay(2000);
  analogWrite(outPin, pumpLOW);
  waterRequest(false);
}
  

int readSensor() {
  /*
  int value = analogRead(0);
  Serial.println(value);
  return value;
  */
  
  int p = random(0,700);
  sensorRequest(p);
  return p;
}

void sensorRequest(int sensorValue){
    HttpClient client;
    client.setHeader("Content-Type: application/json");
    String sensorValueString=String(sensorValue);
    String message = "{	\"type\": \"SENSOR\",	\"value\" : \" "+sensorValueString+" \"}";
    String url = "http://192.168.1.131/event";
    client.post(url, message);
}

void waterRequest(bool on){
    HttpClient client;
    client.setHeader("Content-Type: application/json");
    String message = "";
    if(on){
      message = "{	\"type\": \"WATER_ON\",	\"value\" : \" 0 \"}";
    }else{
       message = "{	\"type\": \"WATER_OFF\",	\"value\" : \" 0 \"}";
    }
    String url = "http://192.168.1.131/event";
    client.post(url, message);
}

void req() {
  // Initialize the client library
  HttpClient client;

  // Make a HTTP request:
//  client.get("http://192.168.1.131/event");
  client.setHeader("Content-Type: application/json");
  client.post("http://192.168.1.131/event", "{	\"type\": \"SETUP\",	\"value\" : \"1234\"}");

//  client.addHeader();  

  // if there are incoming bytes available
  // from the server, read them and print them:
  /*
  while (client.available()) {
    char c = client.read();
    Serial.print(c);
  }
  Serial.flush();
*/
  delay(5000);
}



void loop() {
  int sensor = readSensor();
  Serial.println("SENSOR = "+sensor);
  Serial.flush();
  
  if(sensor < 300){
    twoSecondsPump();
  }
  delay(5000);




}
