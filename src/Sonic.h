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

#ifndef SONIC_H
#define SONIC_H
#include <Arduino.h>

class Sonic {
    public:
        Sonic();
        void attach(uint8_t trig, uint8_t echo);
        long scream(int limMin = 3, int limMax = 800);
        long average(int times = 2, int limMin = 3, int limMax = 800);
    private:
        uint8_t trig;
        uint8_t echo;
        volatile long start;
        volatile long dist;
        volatile bool ready;
        volatile bool measuring;
};

#endif
