#ifndef analog_h
#define analog_h


#define MAX_ANALOG_VALUE 1023

float calculateScaledDifference(float initial, float final, int targetRange);

class AnalogicInput{

    private:

        int _pin;
        int _startRange;
        int _endRange;

    public:

        AnalogicInput(int pin,float startRange = 0, float endRange = 1023);
        int readRealValue();
        float readProcessedValue();

};




#endif 