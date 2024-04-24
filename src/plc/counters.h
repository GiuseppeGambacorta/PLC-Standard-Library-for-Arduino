#ifndef counters_h
#define counters_h
#include "trig.h"

class Counter{

    private:

        int _count;
        R_trig _triggerAdd,_triggerMinus;

    public:

        void update(bool increase, bool decrease);
        void reset();
        int getCount();
        
};



#endif 