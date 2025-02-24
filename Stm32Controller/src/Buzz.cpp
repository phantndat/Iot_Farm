#include "Buzz.h"

void buzzer_Setup(void) {
  pinMode(buzzerPin,OUTPUT);
}

void failLora(void){
    digitalWrite(buzzerPin,HIGH);
      tone(buzzerPin, 3000);    delay(200);
      noTone(buzzerPin);        delay(200);
      tone(buzzerPin, 1000);    delay(200);
      noTone(buzzerPin);
    digitalWrite(buzzerPin,LOW);
}

void failDHT(void){
    digitalWrite(buzzerPin,HIGH);
      tone(buzzerPin, 800);    delay(200);
      noTone(buzzerPin);        delay(200);
      tone(buzzerPin, 800);    delay(200);
      noTone(buzzerPin);
    digitalWrite(buzzerPin,LOW);
}

void changeTimeBuzzer(void){
    digitalWrite(buzzerPin,HIGH);
    tone(buzzerPin, 3000);    delay(300);
    noTone(buzzerPin);        delay(300);
    digitalWrite(buzzerPin,LOW);
}


void resetGatewayIDBuzz(void){
    digitalWrite(buzzerPin,HIGH);
    tone(buzzerPin, 1000);    delay(200);
    noTone(buzzerPin);        delay(200);
    digitalWrite(buzzerPin,LOW);
    delay(200);
    digitalWrite(buzzerPin,HIGH);
    tone(buzzerPin, 2000);    delay(200);
    noTone(buzzerPin);        delay(200);
    digitalWrite(buzzerPin,LOW);
    delay(200);
    digitalWrite(buzzerPin,HIGH);
    tone(buzzerPin, 3000);    delay(200);
    noTone(buzzerPin);        delay(200);
    digitalWrite(buzzerPin,LOW);
}




