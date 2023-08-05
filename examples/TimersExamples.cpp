#include "Arduino.h"
#include <plc.h>




typedef struct Test {
  int count1,count2;
  bool start,stop;
}Test;




Test timerTest;
Input button = Input(0,NC); // using ESP32 normaly closed button, if is NO is not necesary to say that is NO.
Output led = Output(25);

Ton tonTimer = Ton(&timer); //timer is defined in the timers library
Tof tofTimer = Tof(&timer);

R_trig tonTrig;


Tclock tclock_ = Tclock(&timer);




void setup() {

 
}




void loop() {

  timer.update(); // update the time, it works with millis() function

  // absolute time
  timer.getActualMillis();
  timer.getActualSeconds();
  
  // time of the clock
  timer.getHours();
  timer.getMinutes();
  timer.getSeconds();
  timer.getTime(); //time formatted

  tonTimer.update(secondsToMillis(2),button.isActive()); 
  tonTrig.update(tonTimer.output());

  if(tonTrig.output()) {
    timerTest.count1++;
  }


  tofTimer.update(secondsToMillis(5), button.isActive());

  if (tofTimer.output()) {
    led.on();
  } else {
    led.off();
  }

  tofTimer.elapsedTime();
  //tofTimer.stop(); for disable the TOF before of the time.


  tclock_.update(1,button.isActive());
  tclock_.output(); // stay of for 500 seconds and on for 500 seconds
 
  // the trig is on every 1 sec
  if (tclock_.trig()) { 
    timerTest.count2++;
  }
 
  
 

}