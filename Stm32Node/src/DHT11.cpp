#include "dht11.h"

DHT dht(DHTPIN, DHTTYPE);

void turnOnDHT(bool state) {
    digitalWrite(PWR_DHT, state);
}

void DHT11_Read(float *a, float *b) {
    float h = dht.readHumidity();
    float t = dht.readTemperature();
    if (!isnan(h) && !isnan(t)) {
        *a = t;
        *b = h;
    }
}   

void DHT11_Setup(void){
    dht.begin();
    pinMode(PWR_DHT, OUTPUT);
    turnOnDHT(false);
}
