/**
 **************************************************
 *
 * @file        PIR-easyC-SOLDERED.h
 * @brief       Header file for PIR movement sensor.
 *
 *
 * @copyright   GNU General Public License v3.0
 * @authors     Karlo Leksic for soldered.com
 ***************************************************/

#ifndef __PIR_EASYC__
#define __PIR_EASYC__

#include "Arduino.h"
#include "libs/Generic-easyC/easyC.hpp"

class PIRsensor : public EasyC
{
  public:
    PIRsensor(int _pin);
    PIRsensor(void);
    PIRsensor(byte _address);
    bool getState(void);
    void setDelay(uint32_t delayTime);
    bool available();

  protected:
    void initializeNative();

  private:
    int pin;
    bool state = 0;
    uint32_t delayTime = 5000;
};

#endif
