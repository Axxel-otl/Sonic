#ifndef SONIC_H
#define SONIC_H

#include <Arduino.h>

class Sonic {
public:
    Sonic();

    void attach(uint8_t trig, uint8_t echo);
    long scream(int limMin = 3, int limMax = 800);
    long average(int times = 2, int limMin = 3, int limMax = 800);
    void resetSensor();
    static void isr0();
    static void isr1();
    static void isr2();
    static void handleInterrupt(uint8_t id);
private:
    uint8_t trig, echo;
    volatile uint32_t start;
    volatile uint32_t end;
    volatile bool ready;
    volatile bool measuring;
    volatile bool cycleValid;
    static Sonic* pinMap[3];
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