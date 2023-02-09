#ifndef counters_h
#define counters_h
#include "trig.h"

class Counter
{
private:
    int count;
    R_trig triggerAdd,triggerMinus;
public:
    void Update(bool increase = false, bool decrease = false);
    void Reset();
    int GetCount();
};



#endif 