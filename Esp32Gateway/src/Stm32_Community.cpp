#include "Stm32_Community.h"

SoftwareSerial SerialSTM(33, 32);
String dataReceiveSTM = "";
void STM32_Setup(int baud)
{
    SerialSTM.begin(baud);
}

void STM_Transmit_Process(String data)
{
    // Ép kiểu tham số pvParameters thành kiểu con trỏ uint8_t*
    SerialSTM.println(data);
}

String STM_Receive_Process(void)
{
    dataReceiveSTM = "";
    delay(50);
    while (SerialSTM.available() > 0)
    {
        char receivedChar = SerialSTM.read();
        dataReceiveSTM = dataReceiveSTM + receivedChar;
    }
    return dataReceiveSTM;
}