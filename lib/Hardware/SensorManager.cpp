#include "SensorManager.h"

SensorManager::SensorManager(int pinS, int pinD) {
    this->pinSuelo = pinS;
    this->pinDHT = pinD;
    this->dht = new DHT(pinDHT, DHT22);
}

void SensorManager::init() {
    pinMode(pinSuelo, INPUT);
    dht->begin();
}

ContextoAmbiental SensorManager::leerSensores() {
    ContextoAmbiental datos;

    int valorRaw = analogRead(pinSuelo);
    datos.humedadSuelo = map(valorRaw, 3800, 2200, 0, 100);
    datos.humedadSuelo = constrain(datos.humedadSuelo, 0, 100);

    datos.temperaturaAire = dht->readTemperature();
    datos.humedadAire = dht->readHumidity();

    if (isnan(datos.temperaturaAire)) {
        Serial.println("[DHT22] ERROR: Lectura fallida");
        datos.temperaturaAire = 25.0;
    }
    if (isnan(datos.humedadAire)) {
        datos.humedadAire = 50.0;
    }

    Serial.printf("[SENSOR] Raw ADC: %d | Suelo: %.1f%% | Temp: %.1fC | Aire: %.1f%%\n",
        valorRaw, datos.humedadSuelo, datos.temperaturaAire, datos.humedadAire);

    return datos;
}