#include "counters.h"


void Counter::Update(bool increase = false, bool decrease = false){
  triggerAdd.update(increase);
  if (triggerAdd.Q()){
    count++;
  }

  triggerMinus.update(decrease);
  if (triggerMinus.Q()){
    count--;
  }

}


void Counter::Reset(){
  count = 0;
}


int Counter::GetCount(){
  return count;
}