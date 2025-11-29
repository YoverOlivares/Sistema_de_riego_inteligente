#ifndef SENSOR_MANAGER_H
#define SENSOR_MANAGER_H

#include <Arduino.h>
#include <DHT.h>
#include "ContextoAmbiental.h"

class SensorManager {
  private:
    int pinSuelo;
    int pinDHT;
    DHT* dht; // Puntero al objeto sensor

  public:
    SensorManager(int pinSuelo, int pinDHT);
    void init();
    ContextoAmbiental leerSensores();
};

#endif