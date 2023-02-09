#include "trig.h"

void R_trig::update(bool input){

  // Step2: after a cycle disable of the output
   if (this->interlock){
     this->output = false;
   }
   // Step3: Interlock,reset of the trig if i don't detect the input
   if (not input and this->interlock){
      this->interlock =false;
   }
   
   // Step1 :activation of output and enable of the interlock
   if (input and not this->interlock){
       this->output = true;
       this->interlock = true;
   }

  }
bool R_trig::Q(){
  return this->output;
}


void N_trig::update(bool input){

  // Step2: after a cycle disable of the output
   if (output){
     this->output = false;
   }
  
   
   // Step1 :activation  of the interlock
   if (input and not this->interlock){
       this->interlock = true;
   }

    // Step2: Enable the output when there is not anymore the input and reset the interlock
   if (not input and this->interlock){
      this->output = true;
      interlock = false;
   }

  }
bool N_trig::Q(){
  return this->output;
}