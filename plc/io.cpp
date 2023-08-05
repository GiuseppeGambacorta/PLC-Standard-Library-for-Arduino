#include "io.h"
#include <Arduino.h>


Input:: Input(int input_pin, bool normalestate){
   this->_pin = input_pin;
   this->_normalState = normalestate;
   pinMode(this->_pin,INPUT);

  }

bool Input:: isActive(){

    if(this->_normalState == NO){
      return digitalRead(this->_pin);
    }else if (this->_normalState == NC){
      return !digitalRead(this->_pin);
    }
      
  }



Output::Output(int input_pin) {
     
      this->_pin = input_pin;
      pinMode(this->_pin, OUTPUT);
      
    }

void Output::on() {
      digitalWrite(this->_pin, HIGH);
    }

void Output::off() {
      digitalWrite(this->_pin, LOW);
    }

bool Output::isActive(){
      return digitalRead(this->_pin);
    }