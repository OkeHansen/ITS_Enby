#include <WiFi.h>
#include <WiFiUdp.h>
#include <OSCMessage.h>

#define WIFI_SSID " "
#define WIFI_PASS " "

//const char ip[] = "10.163.100.67";
const char ip[] = "10.10.0.66";

#define UDP_PORT 3333
WiFiUDP UDP;
int data1 = 0;
int data2 = 1;
int data3 = 2;



void setup() {
  
  Serial.begin(115200);
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
  OSCMessage msg("/data1/data2/data3");
  msg.add(data1).add(data2).add(data3);
  
  UDP.beginPacket(ip, UDP_PORT);
  msg.send(UDP);
  UDP.endPacket();
  
  sleep(5);
  
}