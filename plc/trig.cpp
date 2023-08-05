#include "trig.h"

void R_trig::update(bool input){

  // Step2: after a cycle disable of the output
   if (this->_interlock){
     this->_output = false;
   }
   // Step3: Interlock,reset of the trig if i don't detect the input
   if (not input and this->_interlock){
      this->_interlock =false;
   }
   
   // Step1 :activation of output and enable of the interlock
   if (input and not this->_interlock){
       this->_output = true;
       this->_interlock = true;
   }

  }
bool R_trig::output(){
  return this->_output;
}


void N_trig::update(bool input){

  
   //without this, at the start of the program the trig goes on  
   if (input){
      this->_active = true;
   }

   // Step2: after a cycle disable of the output
   if (this->_output){
     this->_output = false;
   }
  
   
   // Step1 :activation  of the interlock
   if (input and not this->_interlock){
       this->_interlock = true;
   }

    // Step2: Enable the output when there is not anymore the input and reset the interlock
   if (this->_active and not input and this->_interlock){
      this->_output = true;
      this->_interlock = false;
   }

  }
bool N_trig::output(){
  return this->_output;
}