/*
    * Sonic Library - Ultrasonic Sensor HC-SR04 & IR Analog Sensor
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
    * along with this program. If not, see <https://gnu.org>.
*/

#include "Sonic.h"

Sonic* Sonic::firstInstance = nullptr;

Sonic::Sonic() {
    this->next = nullptr;
    this->ready = false;
    this->measuring = false;
    this->dist = 0;
}

void Sonic::attach(uint8_t trig, uint8_t echo) {
    this->trig = trig;
    this->echo = echo;
    pinMode(this->trig, OUTPUT);
    pinMode(this->echo, INPUT);
    this->next = firstInstance;
    firstInstance = this;
    attachInterrupt(digitalPinToInterrupt(this->echo), Sonic::globalISR, CHANGE);
}

void Sonic::globalISR() {
    Sonic* current = firstInstance;
    while (current != nullptr) {
        int state = digitalRead(current->echo);
        if (state == HIGH && !current->ready) {
            current->start = micros();
        } else if (state == LOW && current->measuring) {
            current->dist = (micros() - current->start) / 58;
            current->ready = true;
            current->measuring = false;
        }
        current = current->next;
    }
}

long Sonic::scream(int limMin, int limMax) {
    if (ready) {
        ready = false;
        long lastDist = dist;
        if (lastDist >= limMin && lastDist <= limMax) {
            return lastDist;
        }
        return -1;
    }
    if (!measuring) {
        digitalWrite(trig, LOW);
        delayMicroseconds(2);
        digitalWrite(trig, HIGH);
        delayMicroseconds(10);
        digitalWrite(trig, LOW);
        measuring = true;
    }
    return -2;
}

long Sonic::average(int times, int limMin, int limMax) {
    long totalDist = 0;
    int validTries = 0;
    for (int i = 0; i < times; i++) {
        long valid = -2;
        uint32_t timeout = millis();
        while (valid == -2) {
            valid = scream(limMin, limMax);
            if (millis() - timeout > 100) break;
        }
        if (valid >= 0) {
            totalDist += valid;
            validTries++;
        }
        delay(30);
    }
    if (validTries == 0) return -1;
    return totalDist / validTries;
}

Infra::Infra() {}

void Infra::attach(uint8_t pin, float A, float B) {
    this->pin = pin;
    this->A = A;
    this->B = B;
    pinMode(this->pin, INPUT);
}

float Infra::read(int limMin, int limMax) {
    float value = analogRead(this->pin);
    if (value <= 0) return -1;
    float d = A * pow(value, B);
    if (d >= limMin && d <= limMax) return d;
    return -1;
}

float Infra::average(int times, int limMin, int limMax) {
    float totalDist = 0;
    int validTries = 0;
    for (int i = 0; i < times; i++) {
        float valid = read(limMin, limMax);
        if (valid != -1) {
            totalDist += valid;
            validTries++;
        }
        delay(10);
    }
    if (validTries == 0) return -1;
    return totalDist / validTries;
}
