#include "nodeId.h"


uint8_t penCodeNums = 5;
uint8_t switchStates = 0;
int penCode = 0;

int nodeId  = 0;

uint8_t reverseBits(uint8_t num, int bitCount) {
    uint8_t reverse_num = 0;
    for (int i = 0; i < bitCount; i++) {
        if (num & (1 << i)) {
            reverse_num |= 1 << (bitCount - 1 - i);
        }
    }
    return reverse_num;
}
// Hàm đọc trạng thái tất cả các switches
void DipSwitch_Setup(void){
    pinMode(DIPSW1, INPUT_PULLUP);
    pinMode(DIPSW2, INPUT_PULLUP);
    pinMode(DIPSW3, INPUT_PULLUP);
    pinMode(DIPSW4, INPUT_PULLUP);
    pinMode(DIPSW5, INPUT_PULLUP);
    pinMode(DIPSW6, INPUT_PULLUP);
    pinMode(DIPSW7, INPUT_PULLUP);
    pinMode(DIPSW8, INPUT_PULLUP);
}

void readAllSwitches(void) {
    switchStates |= (0 << 0);
    switchStates |= (!digitalRead(DIPSW2) << 1);
    switchStates |= (!digitalRead(DIPSW3) << 2);
    switchStates |= (!digitalRead(DIPSW4) << 3);
    switchStates |= (!digitalRead(DIPSW5) << 4);
    switchStates |= (!digitalRead(DIPSW6) << 5);
    switchStates |= (!digitalRead(DIPSW7) << 6);
    switchStates |= (!digitalRead(DIPSW8) << 7);

    uint8_t penCode1 = switchStates & ((1 << penCodeNums) - 1);

    uint8_t nodeId1 = switchStates >> penCodeNums;

    penCode = reverseBits(penCode1, penCodeNums);
    nodeId = reverseBits(nodeId1, 8 - penCodeNums);
    
}