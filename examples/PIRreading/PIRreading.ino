/**
 **************************************************
 *
 * @file        PIRreading.ino
 * @brief       Simple reading example for PIR sensor with easyC
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
    PIR.setDelay(10000);  // Set wanted time in milliseconds to keep the PIR output active when movement is detected - if
                          // you leave this line, the default value will be 2 seconds
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

    delay(1000); // Delay 1 second before next print
}
