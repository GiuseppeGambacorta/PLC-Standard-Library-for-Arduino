#include "counters.h"


void Counter::update(bool increase, bool decrease){
  this->_triggerAdd.update(increase);
  if (this->_triggerAdd.output()){
    _count++;
  }

  this->_triggerMinus.update(decrease);
  if (this->_triggerMinus.output()){
    _count--;
  }

}


void Counter::reset(){
  this->_count = 0;
}


int Counter::getCount(){
  return this->_count;
}