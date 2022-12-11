#include <Arduino.h>
/* #include <WiFi.h>
#include <WiFiUdp.h> */


//sensors
#define lightsensor 33
#define button 17
#define button_2 18
#define trigger 34
#define echo 35
int button_state = 0;
int button_2_state = 0;
int sensed_light = 0;
float duration = 0.00;
float distance = 0.0;
bool receive = 0;
bool object = 0;
bool light = 0;
const float speedOfSound = 0.03432;




void setup() {
  Serial.begin(115200);
  pinMode(lightsensor, INPUT);
  pinMode(button, INPUT);
  pinMode(button_2, INPUT);
  pinMode(trigger, OUTPUT);
  pinMode(echo, INPUT);
  }

void loop() {
  sensed_light = analogRead(lightsensor);
  Serial.println("Lichtsensor: ");
  Serial.println(sensed_light); 
  if (sensed_light < 500){
    light = 1;
  }else{
    light = 0;
  }

  button_state = digitalRead(button);
  Serial.println("Button1: ");
  Serial.println(button_state);

  button_2_state = digitalRead(button_2);
  Serial.println("Button2: ");
  Serial.println(button_2_state); 

  digitalWrite(trigger, HIGH);  
  delay(10);          //delay schwierig, da Code unterbrochen wird. Lieber mit millis
  digitalWrite(trigger, LOW);
  duration = pulseIn(echo, HIGH);
  Serial.println("Dauer: ");
  Serial.println(duration);
  //distance = (duration / 2) * speedOfSound;
  distance = duration / 58; // 2*29us für 1cm in Luft //gibt aktuell nur 0.0 zurück
  Serial.println("Abstand: ");
  Serial.println(distance);

if(Serial.available()>0){
    receive = Serial.read();
    Serial.println("Recieving distance...");
  }
  
  if(distance <= 20.0){
    Serial.println("Object approaching...");
    object = 1;
    }

    else{
    Serial.println("Nothing Close...");
    object = 0;
    }
}