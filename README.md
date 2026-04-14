# Sonic.h library

## Sonic
Class. You can create multiple objects to read multiple sensors at the same time (limited to 3 sensors in current version due to ISR implementation)

### attach(TRIG, ECHO)
Sets trig and echo pins for the sensor instance

### scream(MinimalLimit, MaximalLimit)
default MiL = 3, default MaL = 800 (distance filtering in cm)
Reads the sensor and returns distance

Return values:
- -2 → measurement in progress
- -1 → invalid or out of range
- >=0 → valid distance in cm

### average(Times, MinimalLimit, MaximalLimit)
default Times = 2, other defaults same as scream
Takes multiple readings and returns the average of valid values

---

## Infra
Class. You can create multiple objects to read multiple analog sensors at the same time

### attach(PIN, A, B)
default A = 12343.85, default B = -1.15
Configures analog pin and calibration constants

### read(MinimalLimit, MaximalLimit)
default MiL = 2, default MaL = 400 (distance in cm)
Returns converted distance from analog sensor

### average(Times, MinimalLimit, MaximalLimit)
default Times = 5, same limits as read
Returns average of valid readings

---

## Ideas
- [ ] Add more filtering options beyond average
- [ ] Add support for additional units like inches
- [ ] Expand beyond 3 sensors using platform-specific ISR backend
- [ ] Update examples

---

## Notes
If a value exceeds limits or is invalid it returns -1  
If a reading is not ready yet it returns -2  
Distances are calculated in centimeters internally

---

[![Ask DeepWiki](https://deepwiki.com/badge.svg)](https://deepwiki.com/Axxel-otl/Sonic)

Sorry for my possibly bad English, I'm still learning.  
If you're seeing this, thanks for taking the time to check my library.