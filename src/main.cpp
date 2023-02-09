#include <Arduino.h>
#include "PLC.h"
#include "analog.h"

#define  PULSANTE 5
#define  LED      7
#define  POTENZIOMETRO A4

extern Time time;

AnalogicInput potenziometro = AnalogicInput(POTENZIOMETRO,300);
void setup() {  
  Serial.begin(9600);
}

void loop() {
    time.Count();
    

   
    



    
    Serial.println(potenziometro.ProcessedValue());
    Serial.println(potenziometro.RealValue());
    Serial.println(potenziometro.ProcessedValue() * ((float)(1023 - 100) / 300) + 100);
    delay(500);
   




 
 }
