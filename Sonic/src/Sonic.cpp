/*  
    * Sonic Library - Ultrasonic Sensor HC-SR04  
    * Copyright (c) 2026 Jorge Leonardo Mendoza Hernández
    * MIT License  
*/

#include "Sonic.h"

Sonic::Sonic(){

}

void Sonic::attach(uint8_t trig, uint8_t echo){
    this->trig = trig;
    pinMode(this->trig, OUTPUT);
    this->echo = echo;
    pinMode(this->echo, INPUT);
}

long Sonic::scream(int limMin, int limMax){
    limMax *= 58;
    digitalWrite(this->trig, LOW);
    delayMicroseconds(2);
    digitalWrite(this->trig, HIGH);
    delayMicroseconds(10);
    digitalWrite(this->trig, LOW);
    long dist = pulseIn(this->echo, HIGH, limMax);
    dist /= 58;
    if(dist <= limMin){
        return(-1);
    } else{
        return(dist);
    }
}

long Sonic::average(int times, int limMin, int limMax){
    long dist = 0;
    int validTries = 0;
    for(int i = 0; i < times; i++){
        long valid = scream(limMin, limMax);
        if(valid != -1){
            dist += valid;
            validTries++;
        }
    }
    if(validTries == 0){
        return -1;
    }
    dist /= validTries;
    return dist;
}