#include "Clock.h"


unsigned long Time::Millis_to_Second(unsigned long millis){
      return millis / 1000;

}

void Time::Count(){

    actualmillis = millis();
    actualseconds = Millis_to_Second(actualmillis);
    if (actualseconds >= memtime +1){
        seconds += 1;
        memtime = actualseconds;
    }
 
    if (seconds >= 60){
        minutes += 1;
        seconds = 0;
    }

    if (minutes >= 60){
        minutes = 0;
        hours += 1;
    }
}

unsigned long Time::GetActualMillis(){
    return actualmillis;

}

unsigned long Time::GetActualSeconds(){
    return actualseconds;

}

int Time::GetSeconds(){
    return seconds;

};

int Time::GetMinutes(){
    return minutes;

};


int Time::GetHours(){
    return hours;

};
     
void Time::Reset(){
    seconds = 0;
    minutes = 0;
    hours   = 0;
}


String Time::GetTime(){
 String prova = String(hours);
 prova.concat(":");
 prova.concat((String)minutes);
 prova.concat(":");
 prova.concat((String)seconds);

 return prova;
}
