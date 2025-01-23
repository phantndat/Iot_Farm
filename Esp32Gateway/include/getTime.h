#ifndef GETTIME_H
#define GETTIME_H
#include "time.h"
#include <Arduino.h>
#include "Stm32_Community.h"
#include "MQTT.h"
extern const char *ntpServer;
extern const long gmtOffset_sec; // Offset giờ theo múi giờ (UTC+7 cho Việt Nam)
extern const int daylightOffset_sec;

void getPowerPerMinute(void *);
void getTime_Setup(void);

#endif // LIBRARY_H