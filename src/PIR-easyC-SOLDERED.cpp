/**
 **************************************************
 *
 * @file        Generic-easyC-SOLDERED.cpp
 * @brief       Example functions to overload in base class.
 *
 *
 * @copyright   GNU General Public License v3.0
 * @authors     Karlo Leksic for soldered.com
 ***************************************************/


#include "PIR-easyC-SOLDERED.h"

/**
 * @brief                   PIR native constructor.
 *
 * @param int _pin          Pin on the Arduino connected to PIR sensor.
 */
PIRsensor::PIRsensor(int _pin)
{
    pin = _pin;
    native = 1;
}

/**
 * @brief                   PIR easyC constructor
 */
PIRsensor::PIRsensor()
{
    native = 0;
}

/**
 * @brief                   PIR easyC constructor with address which is not default
 */
PIRsensor::PIRsensor(byte _address)
{
    native = 0;
    address = _address;
}

/**
 * @brief                   Overloaded function for virtual in base class to initialize PIR sensor.
 */
void PIRsensor::initializeNative()
{
    pinMode(pin, INPUT);
}

/**
 * @brief                   Set how long the output will be on high when the sensor is triggered.
 *
 * @param delayTime         Time to hold the output on HIGH after triggering the PIR in seconds.
 *                          Default is 2 seconds.
 */
void PIRsensor::setDelay(uint32_t _delayTime)
{
    delayTime = _delayTime;
    uint8_t *p = (uint8_t *)&delayTime;
    sendData(p, 4);
}

/**
 * @brief                   Function to get state of PIR sensor.
 *
 * @return                  State of the PIR sensor.
 */
bool PIRsensor::getState()
{
    if (native)
    {
        state = digitalRead(pin);
        return state;
    }
    else
    {
        char a;
        readData(&a, 1);
        if (a)
        {
            state = true;
        }
        else
        {
            state = false;
        }

        return state;
    }
}

/**
 * @brief                   The function checks if the PIR is available.
 *
 * @return                  1 if the PIR is available, i if it's not.
 */
bool PIRsensor::available()
{
    Wire.beginTransmission(address);
    if (Wire.endTransmission() == 0)
        return 1;

    return 0;
}
