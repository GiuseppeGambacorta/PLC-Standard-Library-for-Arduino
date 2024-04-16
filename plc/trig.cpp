#include "trig.h"

void R_trig::processInput(bool input){

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
bool R_trig::isActive() const{
   
  return this->output;
}

void R_trig::operator()(bool input){
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



void N_trig::processInput(bool input){

  if (input){
    interlock = true;
  }

   trig.processInput(!input and interlock);

   /*
   //without this, at the start of the program the trig goes on  
   if (input){
      this->active = true;
   }

   // Step2: after a cycle disable of the output
   if (this->output){
     this->output = false;
   }
  
   
   // Step1 :activation  of the interlock
   if (input and not this->interlock){
       this->interlock = true;
   }

    // Step2: Enable the output when there is not anymore the input and reset the interlock
   if (this->active and not input and this->interlock){
      this->output = true;
      this->interlock = false;
   }
   */

  }
bool N_trig::isActive() const{
  return this->trig.isActive();
}