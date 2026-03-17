#include<Sonic.h>

Sonic sonar;

void setup(){
  sonar.attach(12, 11);
  pinMode(13, OUTPUT);
}

void loop(){
  long d = sonar.average(5, 3, 200);
  if(d <= 30){
    digitalWrite(13, HIGH);
  } else{
    digitalWrite(13, LOW);
  }
}