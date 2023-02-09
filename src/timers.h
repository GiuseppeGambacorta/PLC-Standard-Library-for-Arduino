#ifndef timers_h
#define timers_h
#include "Clock.h"
#include "trig.h"


class TON{
    private:
        R_trig trigger;
        long unsigned memory;
        bool interlock,output;
    public:
        void update(int millisecond, bool start, Time* time);
        bool Q();
   
};

class TOF{
    private:
    N_trig trigger;
    long unsigned memory;
    bool interlock,output;
   
    

    public:
    void update(int millisecond, bool start, Time* time);
 
    bool Q();
   

};

#endif 

