#include <Sonic.h>  
  
Sonic sonar1, sonar2, sonar3;  
  
void setup(){  
  sonar1.attach(12, 11);  // Sensor 1  
  sonar2.attach(10, 9);   // Sensor 2    
  sonar3.attach(8, 7);    // Sensor 3  
  Serial.begin(9600);  
}  
  
void loop(){  
  long d1 = sonar1.average(5, 3, 200);  
  long d2 = sonar2.average(5, 3, 200);  
  long d3 = sonar3.average(5, 3, 200);  
    
  Serial.print("Sensor 1: "); Serial.print(d1);  
  Serial.print(" Sensor 2: "); Serial.print(d2);  
  Serial.print(" Sensor 3: "); Serial.println(d3);  
}