#ifndef Clock_h
#define Clock_h
#include "Arduino.h"



class Time{
    private:
     unsigned long actualmillis;
     unsigned long actualseconds;
     unsigned long memtime;
     int seconds,minutes,hours;
     unsigned long Millis_to_Second(unsigned long milliseconds);
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