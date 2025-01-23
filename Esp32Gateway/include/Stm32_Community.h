#ifndef STM32COM_H
#define STM32COM_H

#include <SoftwareSerial.h>
extern SoftwareSerial SerialSTM;
extern String dataReceiveSTM;

void STM32_Setup(int baud);
void STM_Transmit_Process(String data);
String STM_Receive_Process(void);
#endif // LIBRARY_H