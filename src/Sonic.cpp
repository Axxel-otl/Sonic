/*    
    * Sonic Library - Ultrasonic Sensor HC-SR04    
    * Copyright (c) 2026 Jorge Leonardo Mendoza Hernández  
    * MIT License    
*/  
  
#include "Sonic.h"  
  
// Initialize static members  
Sonic** Sonic::sensorInstances = nullptr;  
uint8_t* Sonic::sensorPins = nullptr;  
uint8_t Sonic::sensorCount = 0;  
uint8_t Sonic::maxSensors = 0;  
uint8_t Sonic::totalObjectsCreated = 0;  
  
Sonic::Sonic(){  
    totalObjectsCreated++;  
      
    // Auto-expand capacity if needed  
    if(totalObjectsCreated > maxSensors) {  
        uint8_t newMax = maxSensors == 0 ? 4 : maxSensors * 2;  
          
        // Reallocate arrays  
        Sonic** newInstances = new Sonic*[newMax];  
        uint8_t* newPins = new uint8_t[newMax];  
          
        // Copy existing data  
        for(int i = 0; i < sensorCount; i++) {  
            newInstances[i] = sensorInstances[i];  
            newPins[i] = sensorPins[i];  
        }  
          
        // Clean up old arrays  
        if(sensorInstances) delete[] sensorInstances;  
        if(sensorPins) delete[] sensorPins;  
          
        // Update pointers  
        sensorInstances = newInstances;  
        sensorPins = newPins;  
        maxSensors = newMax;  
    }  
      
    // Initialize instance variables  
    start = 0;  
    dist = 0;  
    ready = false;  
    measuring = false;  
}  
  
void Sonic::attach(uint8_t trig, uint8_t echo){  
    this->trig = trig;  
    pinMode(this->trig, OUTPUT);  
    this->echo = echo;  
    pinMode(this->echo, INPUT);  
      
    // Find existing or add new  
    for(int i = 0; i < sensorCount; i++) {  
        if(sensorPins[i] == echo) {  
            sensorInstances[i] = this;  
            return;  
        }  
    }  
      
    if(sensorCount < maxSensors) {  
        sensorPins[sensorCount] = echo;  
        sensorInstances[sensorCount] = this;  
        sensorCount++;  
    }  
}  
  
long Sonic::scream(int limMin, int limMax){  
    long dist = this->dist;  
    if(ready){  
        ready = false;  
        if(dist >= limMin && dist <= limMax){  
            return(dist);  
        } else{  
            return(-1);  
        }  
    }  
    if(!measuring){  
        digitalWrite(this->trig, LOW);  
        delayMicroseconds(2);  
        digitalWrite(this->trig, HIGH);  
        delayMicroseconds(10);  
        digitalWrite(this->trig, LOW);  
        measuring = true;  
        attachInterrupt(digitalPinToInterrupt(this->echo), isr, CHANGE);  
    }  
    return(-2);  
}  
  
void isr(){  
    for(int i = 0; i < Sonic::sensorCount; i++) {  
        if(digitalRead(Sonic::sensorPins[i]) == HIGH) {  
            Sonic::sensorInstances[i]->start = micros();  
        } else {  
            Sonic::sensorInstances[i]->dist = (micros() - Sonic::sensorInstances[i]->start) / 58;  
            detachInterrupt(digitalPinToInterrupt(Sonic::sensorPins[i]));  
            Sonic::sensorInstances[i]->ready = true;  
            Sonic::sensorInstances[i]->measuring = false;  
        }  
    }  
}  
  
long Sonic::average(int times, int limMin, int limMax){  
    long dist = 0;  
    int validTries = 0;  
    for(int i = 0; i < times; i++){  
        long valid = -2;  
        while(valid == -2){  
            valid = scream(limMin, limMax);  
        }  
        if(valid != -1){  
            dist += valid;  
            validTries++;  
        }  
    }  
    if(validTries == 0){  
        return(-1);  
    }  
    dist /= validTries;  
    return(dist);  
}  
  
void Sonic::cleanup() {  
    if(sensorInstances) {  
        delete[] sensorInstances;  
        sensorInstances = nullptr;  
    }  
    if(sensorPins) {  
        delete[] sensorPins;   
        sensorPins = nullptr;  
    }  
    sensorCount = 0;  
    maxSensors = 0;  
    totalObjectsCreated = 0;  
}