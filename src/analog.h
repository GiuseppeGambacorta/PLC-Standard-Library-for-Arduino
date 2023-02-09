#ifndef analog_h
#define analog_h


class AnalogicInput{
private:
    int pin;
    int range;
public:
    AnalogicInput(int pin,float range);
    int RealValue();
    int ProcessedValue();
};



#endif 