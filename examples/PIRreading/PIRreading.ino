/**
 **************************************************
 *
 * @file        PIRreading.ino
 * @brief       Simple reading example for PIR sensor with easyC
 *
 *  Connect the breakout via easyC to the microcontroller and upload this code on it. When the sensor detects motion,
 *  the getState function returns 1. When there is no movement, the function returns 0.
 *
 *  IMPORTANT: The sensor needs some time for detection. The time is around 5 seconds so if you put in the setDelay
 *  function time lower than 5 seconds, the sensor won't work as you expect.
 *  
 *
 * @link        solde.red/333179
 * @authors     Karlo Leksic for soldered.com
 ***************************************************/

#include "PIR-easyC-SOLDERED.h" //Include Soldered PIR library

PIRsensor PIR; // If using easyC, the constructor is empty

void setup()
{
    Serial.begin(115200); // Start serial comunication on 115200 baud rate
    PIR.begin();          // Begin I2C comunication with default address (0x30)
    PIR.setDelay(10000); // Set wanted time in milliseconds to keep the PIR output active when movement is detected - if
                         // you leave this line, the default value will be 5 seconds which is the minimum to work properly
}

void loop()
{
    if (PIR.getState() == 1) // If movement is detected
    {
        Serial.println("Movement is detected!");
    }
    else // If movement not detected
    {
        Serial.println("There is no movement.");
    }

    delay(1000); // Delay 1 second before next reading
}
