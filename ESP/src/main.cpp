#include <WiFi.h>
#include <WiFiUdp.h>
#include <OSCMessage.h>

#define WIFI_SSID " "
#define WIFI_PASS " "

//const char ip[] = "10.163.100.67";
const char ip[] = "10.10.0.66";

#define UDP_PORT 3333
WiFiUDP UDP;
#define dryer_sensor 33
#define male_sensor 17
#define female_sensor 18
#define sink_sensor 26
#define trigger 32                                                                             
#define echo 35
const int foto_max = 1023;
int h_dryer = foto_max;
int male = foto_max;
int female = foto_max;
int sink = 0;
float duration = 0.0;
float distance = 0.0;
const float speedOfSound = 0.03432;





void setup() {
  
  Serial.begin(115200);
  pinMode(dryer_sensor, INPUT);
  pinMode(male_sensor, INPUT);
  pinMode(female_sensor, INPUT);
  pinMode(sink_sensor, INPUT);
  pinMode(trigger, OUTPUT);
  pinMode(echo, INPUT);
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  Serial.println("set up WiFi");
  
  while (WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(WIFI_SSID);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  WiFi.mode(WIFI_STA);
  /* UDP.begin(UDP_PORT); */
  

}

void loop() {
  digitalWrite(trigger, HIGH);
  delayMicroseconds(2);
  digitalWrite(trigger, LOW);
  delayMicroseconds(10);
  duration = pulseIn(echo, HIGH);
  distance = (duration / 2) * speedOfSound;
  
  h_dryer = analogRead(dryer_sensor);
  Serial.print("Föhn: ");
  Serial.println(h_dryer); 

  sink = analogRead(sink_sensor);
  Serial.print("Wasserhahn: ");
  Serial.println(h_dryer); 

  male = digitalRead(male_sensor);
  Serial.print("Badehose: ");
  Serial.println(male);

  female = digitalRead(female_sensor);
  Serial.print("Bikini: ");
  Serial.println(female); 


  OSCMessage msg("/distance/h_dryer/sink/male/female");
  msg.add(distance).add(h_dryer).add(sink).add(male).add(female);
  
  UDP.beginPacket(ip, UDP_PORT);
  msg.send(UDP);
  UDP.endPacket();
  
sleep(5);
  
}