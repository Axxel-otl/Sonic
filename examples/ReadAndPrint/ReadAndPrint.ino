#include <Sonic.h>

Sonic sonar;

void setup(){
  sonar.attach(12, 11);
  Serial.begin(9600);
}

void loop(){
  long d = sonar.average(5, 3, 200);
  Serial.println(d);
}