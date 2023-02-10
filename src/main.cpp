#include <Arduino.h>
#include "PLC.h"
#include <limits.h>


extern Time time;

String ciao;

void setup() {  
  Serial.begin(9600);
}

void loop() {
    time.Count();
  
   
    ciao.concat((String)time.GetActualSeconds());
    ciao.concat(".");
    ciao.concat("53");
    Serial.println(ciao);
    ciao = "";
    
    
   




 
 }
