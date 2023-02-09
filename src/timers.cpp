#include "timers.h"
#include "Clock.h"


void TON::update(int millisecond,bool start, Time* time){

    trigger.update(start);
    
    if (trigger.Q()){
        memory = time->GetActualMillis();
        interlock = true;
    }

    if (!start){
        interlock=false;
        output = false;
    }

    if (interlock){
        if (time->GetActualMillis() >= (memory + millisecond)){
            output = true;
        
        }
    }
}

bool TON::Q(){
    return output;
}


void TOF::update(int millisecond,bool start, Time* time){

    trigger.update(start);
    

    if (start){
        output = true;
    }



    if (trigger.Q()){
        memory = time->GetActualMillis();
        interlock = true;
    }

 
    if (interlock){
        if (time->GetActualMillis() >= (memory + millisecond)){
            output = false;
            interlock=false;
        
        }
    }



}


bool TOF::Q(){
    return output;
}

