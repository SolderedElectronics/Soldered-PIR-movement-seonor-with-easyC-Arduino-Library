/**
 **************************************************

   @file        attiny_firmware
   @brief       Attiny firmware for PIR with easyC.


   @authors     Karlo Leksic for soldered.com
 ***************************************************/

#include "easyC.h"
#include <Wire.h>

int addr = DEFAULT_ADDRESS;   // 0x30 is default address
byte PIRstate = 0;            // Variable that holds PIR state for sending
uint32_t delayTime;           // Variable for storing delay
byte data[4];                 // Array for receiving delay time in bytes
bool currentState;            // Current PIR state
uint64_t cTime, timeOfChange; // Variables for keeping track of time


void setup()
{
    // Init address pins and set default address
    initDefault();
    addr = getI2CAddress();

    // Init I2C communication
    Wire.begin(addr);
    Wire.onReceive(receiveEvent);
    Wire.onRequest(requestEvent);

    pinMode(PA4, OUTPUT); // Output for led on the breakout
    pinMode(PA5, INPUT);  // Pir's output is attitiny's input

    // Set default values
    cTime = timeOfChange = millis();
    PIRstate = 0;
    delayTime = 5000; // It must not be less than 5 seconds
}

void loop()
{
    cTime = millis(); // Get current time
    currentState = digitalRead(PA5);

    // If the change occurs
    if (currentState == HIGH) 
    {
        // Remember the time when it's occurs
        timeOfChange = millis(); 

        // Set movement variable for sending to 1
        PIRstate = 1;
    }

    // If the movement is detected and waiting time has not passed
    if (PIRstate == 1 && (cTime - timeOfChange < delayTime))
    {
        // Turn on the LED on breakout
        digitalWrite(PA4, HIGH);
    }
    else
    {
        // Set pir state for sending to 0
        PIRstate = 0;

        // Set new current time
        cTime = timeOfChange; // probati bez ovoga

        // Turn off the LED on breakout
        digitalWrite(PA4, LOW);
    }
}

// Define receive event
// Always expecting 4 bytes of data when Dasduino sends the delay time in microseconds
void receiveEvent(int howMany)
{
    int i = 0;
    // Read all data byte by byte and save it to the data array
    while (Wire.available() > 0)
    {
        data[i] = Wire.read();
        i++;
    }

    // Convert received data to the uint32_t
    delayTime = *(uint32_t *)data;
}

// Dasduino only requests the PIR state
void requestEvent()
{
    // Send current PIR state
    Wire.write(PIRstate);
}
