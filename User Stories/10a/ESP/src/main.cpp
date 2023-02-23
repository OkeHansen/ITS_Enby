#include <WiFi.h>
#include <WiFiUdp.h>
#include <OSCMessage.h>

#define WIFI_SSID " "
#define WIFI_PASS " "

const char ip[] = " ";


#define UDP_PORT 3333
WiFiUDP UDP;
#define dryer_sensor 33
#define male_sensor 39
#define female_sensor 34
#define sink_sensor 36
#define trigger 32                                                                             
#define echo 35
#define maxbrightness 1023
int h_dryer = maxbrightness;
int male = maxbrightness;
int female = maxbrightness;
int sink = 0;
float duration = 0.0;
float distance = 0.0;
const float speedOfSound = 0.03432;





void setup() {
  
  pinMode(dryer_sensor, INPUT);
  pinMode(sink_sensor, INPUT);
  pinMode(male_sensor, INPUT);
  pinMode(female_sensor, INPUT);
  
  pinMode(trigger, OUTPUT);
  pinMode(echo, INPUT);
  
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  WiFi.mode(WIFI_STA);   

}

void loop() {
  digitalWrite(trigger, HIGH);
  delayMicroseconds(2);
  digitalWrite(trigger, LOW);
  delayMicroseconds(10);
  duration = pulseIn(echo, HIGH);
  distance = (duration / 2) * speedOfSound;  

  h_dryer = analogRead(dryer_sensor);

  sink = analogRead(sink_sensor);

  male = analogRead(male_sensor);

  female = analogRead(female_sensor);

  OSCMessage msg("/distance/h_dryer/sink/male/female");
  msg.add(distance).add(h_dryer).add(sink).add(male).add(female);
  
  UDP.beginPacket(ip, UDP_PORT);
  msg.send(UDP);
  UDP.endPacket();
}