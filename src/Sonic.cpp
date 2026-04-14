#include "Sonic.h"

Sonic* Sonic::pinMap[3] = {nullptr, nullptr, nullptr};

Sonic::Sonic() {
    ready = false;
    measuring = false;
    cycleValid = false;
    start = 0;
    end = 0;
}

void Sonic::attach(uint8_t trig, uint8_t echo) {
    this->trig = trig;
    this->echo = echo;
    pinMode(trig, OUTPUT);
    pinMode(echo, INPUT);
    for (int i = 0; i < 3; i++) {
        if (pinMap[i] == nullptr) {
            pinMap[i] = this;
            if (i == 0) attachInterrupt(digitalPinToInterrupt(echo), isr0, CHANGE);
            if (i == 1) attachInterrupt(digitalPinToInterrupt(echo), isr1, CHANGE);
            if (i == 2) attachInterrupt(digitalPinToInterrupt(echo), isr2, CHANGE);
            break;
        }
    }
}

long Sonic::scream(int limMin, int limMax) {
    if (!measuring) {
        digitalWrite(trig, LOW);
        delayMicroseconds(2);
        digitalWrite(trig, HIGH);
        digitalWrite(trig, HIGH);
        delayMicroseconds(10);
        digitalWrite(trig, LOW);
        start = micros();
        measuring = true;
        ready = false;
        return -2;
    }
    if (!ready) return -2;
    long duration = end - start;
    long dist = duration / 58;
    measuring = false;
    ready = false;
    if (dist >= limMin && dist <= limMax) return dist;
    return -1;
}

long Sonic::average(int times, int limMin, int limMax) {

    long total = 0;
    int count = 0;
    for (int i = 0; i < times; i++) {
        long v = -2;
        uint32_t t = millis();
        while (v == -2) {
            v = scream(limMin, limMax);
            if (millis() - t > 100) break;
        }
        if (v >= 0) {
            total += v;
            count++;
        }
        delay(30);
    }
    if (count == 0) return -1;
    return total / count;
}

void Sonic::resetSensor() {
    ready = false;
    measuring = false;
    cycleValid = false;
    start = 0;
    end = 0;
}

void Sonic::handleInterrupt(uint8_t id) {
    Sonic* s = pinMap[id];
    if (!s) return;
    uint32_t now = micros();
    if (digitalRead(s->echo) == HIGH) {
        s->start = now;
        s->measuring = true;
        s->cycleValid = false;
    } else {
        s->end = now;
        s->ready = true;
        s->cycleValid = true;
    }
}

void Sonic::isr0() { handleInterrupt(0); }
void Sonic::isr1() { handleInterrupt(1); }
void Sonic::isr2() { handleInterrupt(2); }

Infra::Infra() {}

void Infra::attach(uint8_t pin, float A, float B) {
    this->pin = pin;
    this->A = A;
    this->B = B;
    pinMode(pin, INPUT);
}

float Infra::read(int limMin, int limMax) {
    float v = analogRead(pin);
    if (v <= 0) return -1;
    float d = A * pow(v, B);
    if (d >= limMin && d <= limMax) return d;
    return -1;
}

float Infra::average(int times, int limMin, int limMax) {
    float total = 0;
    int count = 0;
    for (int i = 0; i < times; i++) {
        float v = read(limMin, limMax);
        if (v != -1) {
            total += v;
            count++;
        }
        delay(10);
    }
    if (count == 0) return -1;
    return total / count;
}