#include "analog.h"
#include "Arduino.h"

AnalogicInput::AnalogicInput(int pin, float range){
 this->pin = pin;
 this->range = range;

}


int AnalogicInput::RealValue(){
    return analogRead(this->pin);
}


int AnalogicInput::ProcessedValue(){
    int scaledvalue = (RealValue() - 100) * ((float)this->range / (float)(1023 - 100));

    if (RealValue() < 100){
        scaledvalue = 0;
    }
    return scaledvalue;
    
}