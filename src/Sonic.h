/*
    * Sonic Library - Ultrasonic Sensor HC-SR04 & IR Analog Sensor
    * Copyright (c) 2026 Jorge Leonardo Mendoza Hernández
    * 
    * Licensed under the GNU General Public License, Version 3.0 (the "License");
    * you may not use this file except in compliance with the License.
    * You may obtain a copy of the License at
    * 
    *     https://gnu.org
    * 
    * Unless required by applicable law or agreed to in writing, software
    * distributed under the License is distributed on an "AS IS" BASIS,
    * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
*/

#ifndef SONIC_H
#define SONIC_H
#include <Arduino.h>

class Sonic {
    public:
        Sonic();
        void attach(uint8_t trig, uint8_t echo);
        long scream(int limMin = 3, int limMax = 800);
        long average(int times = 2, int limMin = 3, int limMax = 800);
        static void globalISR();
    private:
        uint8_t trig, echo;
        volatile uint32_t start;
        volatile long dist;
        volatile bool ready, measuring;
        Sonic* next;
        static Sonic* firstInstance;
};

class Infra {
    public:
        Infra();
        void attach(uint8_t pin, float A = 12343.85, float B = -1.15);
        float read(int limMin = 2, int limMax = 400);
        float average(int times = 5, int limMin = 2, int limMax = 400);
    private:
        uint8_t pin;
        float A, B;
};

#endif