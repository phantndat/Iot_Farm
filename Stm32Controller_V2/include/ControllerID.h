#ifndef NODEID_H
#define NODEID_H
#include <Arduino.h>
#include "Buzz.h"
#include <EEPROM.h>
    extern int penCode, nodeId;
    // Định nghĩa chân DIP switches
    #define DIPSW1 PA7
    #define DIPSW2 PB8
    #define DIPSW3 PA8
    #define DIPSW4 PB15
    #define DIPSW5 PB14
    #define DIPSW6 PB13
    #define DIPSW7 PB12
    #define DIPSW8 PB9
    void readAllSwitches(void);
    void DipSwitch_Setup(void);
#endif