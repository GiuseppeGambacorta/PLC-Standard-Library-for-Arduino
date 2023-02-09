#include <Arduino.h>

#include "PLC.h"
#include "counters.h"



#define  PULSANTE 5
#define  LED      7

extern Time time;

Counter ciaone;


N_trig prova;
Input button = Input(PULSANTE);
Output led = Output(LED);
TON wewe;

int conteggio = 0;

void setup() {  
  Serial.begin(9600);
}

void loop() {
    time.Count();
    ciaone.Update(button.IsActive(),wewe.Q());
    
    prova.update(button.IsActive());
    wewe.update(3000,button.IsActive(),&time);

   

    if (prova.Q())
    {
      conteggio += 1;
    }
    

    led.On();


    if (button.IsActive()){
      led.Off();
     
    }
    Serial.println(ciaone.GetCount());
    //Serial.println(time.GetActualMillis());


    
    
 digitalWrite(LED_BUILTIN,HIGH);

 
 }
