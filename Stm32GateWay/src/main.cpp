#include <Arduino.h>
#include "espCom.h"
#include "pzem.h"

void setup(){
  SerialEsp_Setup(9600);
  initRelays();
  SerialPzem_Setup(9600);

  TIM_TypeDef *Instance = TIM3;
  HardwareTimer *MyTim = new HardwareTimer(Instance);
  MyTim->setOverflow(1000000, MICROSEC_FORMAT);
  MyTim->attachInterrupt(Pzem_Read);
  MyTim->resume();  
}

void loop(){
  Esp_Receive();
  delay(50);
}


