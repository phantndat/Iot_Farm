#ifndef DHT11_H  
#define DHT11_H
#include <Arduino.h>
#include "DHT.h"
#include <Adafruit_Sensor.h>
#include "Buzz.h"
#define DHTPIN PA3
#define DHTTYPE DHT11

#define PWR_DHT  PB5

extern DHT dht;

void turnOnDHT(bool state);
void DHT11_Read(float *a, float *b);
void DHT11_Setup(void);

#endif 