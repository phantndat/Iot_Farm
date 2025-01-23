#include <Arduino.h>
#include <lora.h>
#include <ControllerID.h>
#include <Relays.h>
#include <Buzz.h>

// put function declarations here:
int myFunction(int, int);

void setup() {
  loraInit();
  initRelays();
  DipSwitch_Setup();
  readAllSwitches();
}

void loop() {
  // put your main code here, to run repeatedly:
}

// put function definitions here:
int myFunction(int x, int y) {
  return x + y;
}