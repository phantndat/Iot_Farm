#ifndef PZEM_H
#define PZEM_H
#include <PZEM004Tv30.h>

extern PZEM004Tv30 pzem;

extern float current;
extern float power;
void SerialPzem_Setup(int baud);

void cleanup();
void Pzem_Read(void);
float getPowerAverage(void);
#endif // LIBRARY_H