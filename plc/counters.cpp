#include "counters.h"


void Counter::update(bool increase, bool decrease){
  this->_triggerAdd.processInput(increase);
  if (this->_triggerAdd.isActive()){
    _count++;
  }

  this->_triggerMinus.processInput(decrease);
  if (this->_triggerMinus.isActive()){
    _count--;
  }

}


void Counter::reset(){
  this->_count = 0;
}


int Counter::getCount(){
  return this->_count;
}