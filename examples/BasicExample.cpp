#include "Arduino.h"
#include <plc.h>



typedef struct Test {
  int count1,count2;
  bool start,stop;
}Test;

Test buttonTest;
Input button = Input(0,NC); // using ESP32 normaly closed button, if is NO is not necesary to say that is NO.
Output led = Output(25);
R_trig buttonTrigRising;
N_trig buttonTrigFalling;
Counter counter;
AnalogicInput sensor = AnalogicInput(36,0,100);


void setup() {
   
}


void loop() {
 
  if (button.isActive()) {
    led.on();
  } else {
    led.off();
  }

  buttonTrigRising.update(button.isActive());
  buttonTrigFalling.update(button.isActive());

  if(buttonTrigRising.output()) {
    buttonTest.count1++;
  }

  if (buttonTrigFalling.output()) {
    buttonTest.count2++;
  }


  counter.update(led.isActive(),false);
  if (counter.getCount() >= 10){
    counter.reset();
  }


  if (sensor.readRealValue() > 900){

      // do stuff
  }

  if (sensor.readProcessedValue() > 50){

      // do stuff
  }

}