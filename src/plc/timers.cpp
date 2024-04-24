#include "timers.h"




static long unsigned countTime(unsigned long actualTime, unsigned long oldTime){

    return actualTime - oldTime;
}


long unsigned secondsToMillis(long unsigned input){
        return input * 1000;
}

long unsigned minutesToMillis(long unsigned input){
        return secondsToMillis(input*60);
}

long unsigned hoursToMillis(long unsigned input){
        return minutesToMillis(input*60);
}

long unsigned millisToSeconds(long unsigned input){
        return input / 1000;
}

#pragma region Timer
void Timer::update(){

    this->_actualMillis = millis();
    
    if (this->_actualMillis - this->_oldMillis >= 1000){
        this->_actualSeconds++;
        this->_oldMillis = this->_actualMillis;
    }
    

    if (this->_actualSeconds - this->_oldSeconds >= 1){
        this->_seconds += 1;
        this->_oldSeconds = this->_actualSeconds;
    }
 
    if (this->_seconds >= 60){
        this->_minutes += 1;
        this->_seconds = 0;
    }

    if (this->_minutes >= 60){
        this->_minutes = 0;
        this->_hours += 1;
    }
}

unsigned long Timer::getActualMillis(){
    return this->_actualMillis;

}

unsigned long Timer::getActualSeconds(){
    return this->_actualSeconds;

}

int Timer::getSeconds(){
    return this->_seconds;

};

int Timer::getMinutes(){
    return this->_minutes;

};


int Timer::getHours(){
    return this->_hours;

};
     
void Timer::reset(){
    this->_seconds = 0;
    this->_minutes = 0;
    this->_hours   = 0;
}


String Timer::getTime(){
 String timeString = String(this->_hours);
 timeString.concat(":");
 timeString.concat((String)this->_minutes);
 timeString.concat(":");
 timeString.concat((String)this->_seconds);

 return timeString;
}


#pragma endregion



#pragma region TON
Ton::Ton(Timer* t){
    this->_time = t;
    this->_memory = 0;
    
}


void Ton::update(unsigned long milliseconds,bool start){

    this->_internalTime = milliseconds;
    this->_trigger.processInput(start);
    
    // #1 save the actual time
    if (this->_trigger.isActive()){
        this->_memory = _time->getActualMillis();
        this->_interlock = true;
    }


    if (!start){
        this->_interlock=false;
        this->_output = false;
    }

    // #2 check if the time has passed  
    if (this->_interlock){
        if (countTime(this->_time->getActualMillis(), this->_memory) >= this->_internalTime){
            this->_output = true;
        
        }
    }
}

long unsigned Ton::elapsedTime(){

    if (this->_interlock){

            
            if (countTime(this->_time->getActualMillis(),this->_memory) <= this->_internalTime){

                return countTime(this->_time->getActualMillis(),this->_memory);
            }
            else{
                return this->_internalTime;
            }

    }
    else{
        return 0;
    }

    
}

bool Ton::output(){
    return this->_output;
}

#pragma endregion

#pragma region TOF
Tof::Tof(Timer* t){
    this->_time = t;
    this->_memory = 0;
}


void Tof::update(int milliseconds,bool start){

    this->_internalTime = milliseconds;
    this->_trigger.update(start);
    
 
    if (this->_trigger.output()){
        this->_memory = this->_time->getActualMillis();
        this->_interlock = true;
    }


    if (start){
        this->_output = true;
        this->_interlock = false;
        this->_memory = 0;
    }
 
    if (this->_interlock){
        if (countTime(this->_time->getActualMillis(), this->_memory)>= this->_internalTime){
            this->_output = false;
            this->_interlock=false;   
        }
    }

}
// input su, fino a quando non parte ton, input su, quando parte ton giu
//timer interface, con metodi in comune nel caso
//filtro analogico copiato dal tipo
// aggiungi override operator, nei trig, quindi nell'interfaccia
// aggiungi override operator anche nel counter, nel timer, e nei timer
//aggiorna cartella github, markdown, guarda arduino CI, prima release, aggiungere ad arduino?
// fare schema UML della libreria
bool Tof::output(){
    return this->_output;
}

void Tof::stop(){
    this->_interlock = false;
    this->_output = false;
    this->_memory = 0;
}

long unsigned Tof::elapsedTime(){

    if (this->_interlock){

            if (countTime(this->_time->getActualMillis(),this->_memory) <= this->_internalTime){

                return countTime(this->_time->getActualMillis(),this->_memory);
            }
            else{
                return this->_internalTime;
            }

    }
    else{
        return 0;
    }

}

#pragma endregion



Tclock::Tclock(Timer* t) : _actualOutput(t), _interlock(t){

    this->_time = t;

}

void Tclock::update(float timeForSecond, bool start){

    this->_trigSignal.update(this->_actualOutput.output());

    this->_interlockTrig.update(this->_state   &&   !this->_actualOutput.output());
    this->_actualClockTrig.update(this->_state && this->_interlock.output());

    switch (this->_state)
    {

        case 0:
            
            if (start && timeForSecond > 0){
                this->_state = 1;
            }
            break;

        case 1:

            this->_interlock.update((1000.0/timeForSecond)/2, this->_interlockTrig.output());
            this->_actualOutput.update( (1000.0/timeForSecond)/2, this->_actualClockTrig.output());    
            
            if (!start){
                _actualOutput.stop();
                _interlock.stop();
                this->_state = 0;
            }

            break;
            

    }

    this->_output = this->_actualOutput.output();
    this->_trig = this->_trigSignal.output();    
 
}

long unsigned int Tclock::prova(){
    return this->_actualOutput.elapsedTime();
}

long unsigned int Tclock::prova2(){
    return this->_interlock.elapsedTime();
}

bool Tclock::output(){
    return this->_output;
}

bool Tclock::trig(){
    return this->_trig;
}

