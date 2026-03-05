### Initial version
## Sonic
Class. You can create multiple objects to read multiple sensors at the same time
## attach(TRIG, ECHO)
With this you can set trig and echo pins to a certain sensor to use it
## scream(MinimalLimit, MaximalLimit)
*default MiL = 3, default MaL = 800*
With this you can read the sensor's value
## average(Times, MinimalLimit, MaximalLimit)
*default Times = 2, the other's default is the same as in scream*
With this you can scream the times you want and then average them
## Ideas
- [ ] Modify the scream to turn it into a non-blocking thing
- [ ] Create more filters for the lectures (Like the average I have)
## Notes
If a value exceeds the limits or the value isn't valid it returns -1

Sorry for my possibly bad english, i'm learning
If you're seeing this thank you for taking the time to see my library
