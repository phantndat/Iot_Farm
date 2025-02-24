#include <Arduino.h>
#include "espCom.h"
#include "pzem.h"

void setup(){
  SerialEsp_Setup(9600);  // Khởi tạo Serial giao tiếp với ESP
  initRelays();           // Khởi tạo relay
  SerialPzem_Setup(9600); // Khởi tạo Serial giao tiếp PZEM

 //Cấu hình timer
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


