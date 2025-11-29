#include "SensorManager.h"

SensorManager::SensorManager(int pinS, int pinD) {
    this->pinSuelo = pinS;
    this->pinDHT = pinD;
    // Instanciamos el DHT (Tipo DHT22)
    this->dht = new DHT(pinDHT, DHT22);
}

void SensorManager::init() {
    pinMode(pinSuelo, INPUT);
    dht->begin();
}

ContextoAmbiental SensorManager::leerSensores() {
    ContextoAmbiental datos;

    // 1. Lectura de Humedad de Suelo (Analógica)
    int valorRaw = analogRead(pinSuelo);
    // Mapeo: 0 (0V) -> 0%, 4095 (3.3V) -> 100%
    // Nota: Calibra estos valores mín/máx con tu sensor real en agua/aire
    datos.humedadSuelo = map(valorRaw, 0, 4095, 0, 100);

    // 2. Lectura Ambiental (Digital)
    datos.temperaturaAire = dht->readTemperature();
    datos.humedadAire = dht->readHumidity();

    // 3. Validación de errores (NaN)
    if (isnan(datos.temperaturaAire)) datos.temperaturaAire = 25.0; // Default seguro
    if (isnan(datos.humedadAire)) datos.humedadAire = 50.0;

    return datos;
}