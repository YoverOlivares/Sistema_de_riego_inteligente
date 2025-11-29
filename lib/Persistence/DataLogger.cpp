#include "DataLogger.h"

void DataLogger::init() {
    // Aquí inicializaríamos la tarjeta SD: SD.begin()...
    Serial.println("[DataLogger] Sistema de archivos simulado listo.");
}

void DataLogger::guardarLectura(ContextoAmbiental datos) {
    // SPRINT 1: Volcado a Serial con formato CSV para recolección de Dataset
    // Formato: Suelo, Temp, Aire, TiempoDecidido
    Serial.print(datos.humedadSuelo);
    Serial.print(",");
    Serial.print(datos.temperaturaAire);
    Serial.print(",");
    Serial.print(datos.humedadAire);
    Serial.print(",");
    Serial.println(datos.tiempoRiegoCalculado);
}