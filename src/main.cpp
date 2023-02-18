#include <Arduino.h>
#include "PLC.h"
#include <limits.h>


extern Time time;
typedef struct message
{
  int count[2];
   
}message;


String MessageToSend(message *var){
  String sendmessage;
  unsigned int i;
  for ( i = 0; i < sizeof(var->count) / sizeof(var->count[0]) -1; i++)
  {
    sendmessage.concat((String)var->count[i]);
    sendmessage.concat("!");
   
  }
  
  sendmessage.concat((String)var->count[i]);
  sendmessage.concat("\n");
  return sendmessage;
}


message prova;
int array[20];
float average;
unsigned int i;
unsigned int x;
AnalogicInput sensore = AnalogicInput(14);

void setup() {  
  Serial.begin(9600);
}

void loop() {
    time.Count();

    /*
    
    for ( i = 0; i < sizeof(prova.count) / sizeof(prova.count[0]); i++)
    {
       prova.count[i] = time.GetSeconds() + i;
    }

    */

   
   if (x >= 20){
     x = 0;
   }
   array[x] = sensore.ReadRealValue();
   x++;
    average = 0;
    for ( i = 0; i < 20; i++)
    {
       average += (float)array[i] / 20.0;
       
    }
    
    prova.count[0] = sensore.ReadRealValue();
    prova.count[1] = average ;
    
    Serial.println(MessageToSend(&prova));
    //Serial.println(average);
    delay(200);
    
    
    
   




 
 }
