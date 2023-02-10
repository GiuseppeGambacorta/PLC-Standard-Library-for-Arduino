#include "analog.h"
#include "Arduino.h"

AnalogicInput::AnalogicInput(int pin, float range){
 this->pin = pin;
 this->range = range;

}


int AnalogicInput::ReadRealValue(){
    return analogRead(this->pin);
}


int AnalogicInput::ReadProcessedValue(){
    int actualvalue = ReadRealValue();
    int scaledvalue = (actualvalue - 0) * ((float)this->range / (float)(1023 - 0)); // same as map

    if (actualvalue < 100){
        scaledvalue = 0;
    }
    return scaledvalue;
    
}


