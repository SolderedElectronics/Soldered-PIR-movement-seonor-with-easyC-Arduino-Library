/**
 **************************************************

   @file        attiny_firmware
   @brief       Attiny firmware for PIR with easyC.



   @authors     Karlo Leksic for soldered.com
 ***************************************************/

#include "easyC.h"
#include <Wire.h>

int addr = DEFAULT_ADDRESS;
byte PIRstate = 0;
uint32_t delayTime; 
byte data[4];
bool currentState;
uint64_t cTime, timeOfChange;


void setup()
{
  initDefault();
  addr = getI2CAddress();

  Wire.begin(addr);
  Wire.onReceive(receiveEvent);
  Wire.onRequest(requestEvent);

  pinMode(PA4, OUTPUT); // Output for led on the breakout
  pinMode(PA5, INPUT);  // Pir's output is attitiny's input

  cTime = timeOfChange = millis();
  PIRstate = 0;
  delayTime = 5000;
}

void loop()
{
  cTime = millis();
  currentState = digitalRead(PA5);  
  if (currentState == HIGH) // If the change occurs
  {
    timeOfChange = millis(); // Remember the time when it's occurs
    PIRstate = 1;
  }

  if (PIRstate == 1 && (cTime - timeOfChange <= delayTime))
  {
    digitalWrite(PA4, HIGH);
  }
  else
  {
    PIRstate = 0;
    cTime = timeOfChange;
    digitalWrite(PA4, LOW);
  }
}


void receiveEvent(int howMany)
{
  int i = 0;
  while (Wire.available() > 0)
  {
    data[i] = Wire.read();
    i++;
  }
  delayTime = *(uint32_t *)data;
}

void requestEvent()
{
  Wire.write(PIRstate);
}
