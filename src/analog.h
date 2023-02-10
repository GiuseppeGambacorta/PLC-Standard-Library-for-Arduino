#ifndef analog_h
#define analog_h


class AnalogicInput{
private:
    int pin;
    int range;
public:
    AnalogicInput(int pin,float range = 1023);
    int ReadRealValue();
    int ReadProcessedValue();
};




#endif 