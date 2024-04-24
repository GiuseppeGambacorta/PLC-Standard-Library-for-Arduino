#ifndef timers_h
#define timers_h
#include "trig.h"
#include "Arduino.h"



static long unsigned countTime(unsigned long actualTime, unsigned long oldTime);
long unsigned secondsToMillis(long unsigned input);
long unsigned minutesToMillis(long unsigned input);
long unsigned hoursToMillis(long unsigned input);

long unsigned millisToSeconds(long unsigned input);


class Timer{

    private:

        unsigned long _oldMillis;
        unsigned long _actualMillis;
        unsigned long _actualSeconds;
        unsigned long _oldSeconds;
        int _seconds,_minutes,_hours;

    public:

        void update();
        unsigned long getActualMillis();
        unsigned long getActualSeconds();
        int getSeconds();
        int getMinutes();
        int getHours();
        void reset();
        String getTime();
};

// Autodeclared when the library is imported
static Timer timer;


class Ton{

    private:

        R_trig _trigger;
        long unsigned _memory,_internalTime;
        bool _interlock,_output;
        Timer *_time;

    public:

        Ton(Timer *t);
        void update(long unsigned milliseconds, bool start);
        long unsigned elapsedTime();
        bool isActive();
   
};

class Tof{

    private:

        N_trig _trigger;
        long unsigned _memory,_internalTime;
        bool _interlock,_output;
        Timer *_time;
   
    public:

        Tof(Timer *t);
        void update(int milliseconds, bool start);
        void stop();
        long unsigned elapsedTime();
        bool isActive();

   
};


class Tclock{
    private:

        N_trig _actualClockTrig;
        R_trig _interlockTrig;
        Tof _actualOutput, _interlock;
        Timer *_time;
        N_trig _trigSignal;
        bool _state;
        bool _output,_trig;

    public:

        Tclock(Timer *t) ;
        void update(float timeForSeconds, bool start);
        bool output();
        bool trig();
        long unsigned int prova();
        long unsigned int prova2();

};
#endif 

