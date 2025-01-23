#include "buzzer.h"
int buzzerPin = 22;

void buzzer_Setup()
{
  pinMode(buzzerPin, OUTPUT);
}

void buzzer_wait_to_connect_wifi()
{
  tone(buzzerPin, 2000);
  delay(800);

  noTone(buzzerPin);
  delay(1000);
}

void buzzer_fail_Lora()
{
  for (int i = 0; i < 3; i++)
  {
    tone(buzzerPin, 1000);
    delay(200);

    noTone(buzzerPin);
    delay(200);
  }
  delay(1500);
}
void buzzer_resetWiFi()
{
  for (int i = 0; i < 3; i++)
  {
    tone(buzzerPin, 3000);
    delay(500);

    noTone(buzzerPin);
    delay(200);
  }
}
void buzzer_resetWiFi_Succes()
{
  tone(buzzerPin, 3000);
  delay(800);

  noTone(buzzerPin);
  delay(300);
  for (int i = 0; i < 2; i++)
  {
    tone(buzzerPin, 4000);
    delay(100);

    noTone(buzzerPin);
    delay(100);
  }
}
void buzzer_fail_mqtt()
{
  for (int i = 0; i < 2; i++)
  {
    tone(buzzerPin, 1000);
    delay(200);

    noTone(buzzerPin);
    delay(200);
  }
  delay(500);
}
void cannot_get_time()
{
  for (int i = 0; i < 3; i++)
  {
    tone(buzzerPin, 3500 - (500 * i));
    delay(200);

    noTone(buzzerPin);
    delay(200);
  }
  delay(500);
}