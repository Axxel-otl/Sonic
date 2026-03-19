#include <Sonic.h>

Sonic sonar;

void setup(){
  sonar.attach(12, 11);
  Serial.begin(9600);
}

void loop(){
  long d = sonar.scream(3, 200);
  if(d == -2) return;
  if(d == -1){
    Serial.println("Invalid reading");
    return;
  }
  Serial.println(d);
}