#include "io.h"
#include <Arduino.h>

Input:: Input(int input_pin){
   this->_pin = input_pin;
    pinMode(this->_pin,INPUT);
  }
bool Input:: IsActive(){
      return digitalRead(this->_pin);
  }





Output::Output(int input_pin) {
     
      this->_pin = input_pin;
      pinMode(_pin, OUTPUT);
      
    }
void Output::On() {
      digitalWrite(_pin, HIGH);
    }
void Output::Off() {
      digitalWrite(_pin, LOW);
    }
bool Output::IsActive(){
      return digitalRead(_pin);
    }