/*    
    * Sonic Library - Ultrasonic Sensor HC-SR04    
    * Copyright (c) 2026 Jorge Leonardo Mendoza Hernández  
    * MIT License    
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
        static void cleanup();  // Optional cleanup method  
    private:  
        uint8_t trig;  
        uint8_t echo;  
        volatile long start;  
        volatile long dist;  
        volatile bool ready;  
        volatile bool measuring;  
          
        // Auto-scaling static members  
        static Sonic** sensorInstances;  
        static uint8_t* sensorPins;  
        static uint8_t sensorCount;  
        static uint8_t maxSensors;  
        static uint8_t totalObjectsCreated;  
};  
  
#endif