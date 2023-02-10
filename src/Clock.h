#ifndef Clock_h
#define Clock_h
#include "Arduino.h"



class Time{
    private:
    unsigned long oldmillis;
     unsigned long actualmillis;
     unsigned long actualseconds;
     unsigned long oldseconds;
     int seconds,minutes,hours;
    public:

     void Count();
     unsigned long GetActualMillis();
     unsigned long GetActualSeconds();
     int GetSeconds();
     int GetMinutes();
     int GetHours();
     void Reset();
     String GetTime();
};

static Time time;






#endif