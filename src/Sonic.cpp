/*
 * Sonic Library - Ultrasonic Sensor HC-SR04
 * Copyright (c) 2026 Jorge Leonardo Mendoza Hernández
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <https://www.gnu.org/licenses/>.
 */

#include "Sonic.h"

Sonic::Sonic(){

}

static Sonic* instance = nullptr;

void Sonic::attach(uint8_t trig, uint8_t echo){
    instance = this;
    this->trig = trig;
    pinMode(this->trig, OUTPUT);
    this->echo = echo;
    pinMode(this->echo, INPUT);
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
    if(digitalRead(instance->echo) == HIGH){
        instance->start = micros();
    } else{
        instance->dist = (micros()-instance->start)/58;
        detachInterrupt(digitalPinToInterrupt(instance->echo));
        instance->ready = true;
        instance->measuring = false;
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
