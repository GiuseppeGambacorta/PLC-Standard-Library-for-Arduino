#include "analog.h"
#include "Arduino.h"




float calculateScaledRange(float startRange, float endRange, int actualValue) {

    if (startRange < endRange && startRange >= 0 && endRange <= MAX_ANALOG_VALUE) {
        float range = endRange - startRange;
        return actualValue * (range / MAX_ANALOG_VALUE);
    }
}


AnalogicInput::AnalogicInput(int pin, float startRange, float endRange){
    this->_pin = pin;
    this->_startRange = startRange;
    this->_endRange = endRange;
}


int AnalogicInput::readRealValue(){
    return analogRead(this->_pin);
}


float AnalogicInput::readProcessedValue(){
    return calculateScaledRange(this->_startRange,this->_endRange,this->readRealValue());
}


