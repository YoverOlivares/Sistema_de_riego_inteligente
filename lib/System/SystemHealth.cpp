#include "SystemHealth.h"
#include <Arduino.h>

bool SystemHealth::verificarSensores() {
    // SPRINT 1: Simulamos que todo está OK.
    // En el futuro, leeríamos si el DHT responde.
    return true; 
}

float SystemHealth::obtenerBateria() {
    // SPRINT 1: Simulamos batería llena
    return 100.0;
}