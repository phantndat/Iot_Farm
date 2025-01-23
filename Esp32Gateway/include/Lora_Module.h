#ifndef LORAMODULE_H
#define LORAMODULE_H

#include <SPI.h>
#include <LoRa.h>
#include "buzzer.h"
#include <vector>
#define LORA_CS 5    // Chip Select
#define LORA_RST 4   // Reset
#define LORA_IRQ 2   // DIO0 (IRQ)
#define LORA_SCK 18  // SCK
#define LORA_MISO 19 // MISO
#define LORA_MOSI 23 // MOSI

extern std::vector<String> receivedDataList;

extern bool LoraSender;
void Lora_Setup();
void Lora_receive(void *);
void resetLoRaModule();
#endif // LIBRARY_H