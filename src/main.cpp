#include <Arduino.h>
#include "ContextoAmbiental.h"
#include "SensorManager.h"
#include "PumpController.h"
#include "IrrigationBrain.h"
#include "DataLogger.h"
#include "SystemHealth.h"

#define PIN_DHT 15
#define PIN_SUELO 34
#define PIN_RELE 26

SensorManager sensores(PIN_SUELO, PIN_DHT);
PumpController bomba(PIN_RELE);
IrrigationBrain cerebro;
DataLogger logger;
SystemHealth monitor;

void setup() {
    pinMode(PIN_RELE, OUTPUT);
    digitalWrite(PIN_RELE, LOW);

    Serial.begin(115200);
    delay(1000);
    Serial.println("\n>>> INICIANDO ECORIEGO AI <<<");

    sensores.init();
    bomba.init();
    logger.init();
    cerebro.init();

    Serial.println(">>> Sistema listo.");
}

void loop() {
    if (!monitor.verificarSensores()) {
        Serial.println("ERROR: Fallo en sensores. Reintentando...");
        delay(5000);
        return;
    }

    ContextoAmbiental ctx = sensores.leerSensores();
    ctx.tiempoRiegoCalculado = cerebro.calcularRiego(ctx);
    logger.guardarLectura(ctx);

    if (ctx.tiempoRiegoCalculado > 1.0) {
        Serial.print(" -> REGANDO ");
        Serial.print(ctx.tiempoRiegoCalculado);
        Serial.println(" seg — Rele ACTIVADO");
        bomba.activar(ctx.tiempoRiegoCalculado);
        Serial.println(" -> Riego finalizado. Rele APAGADO");
        delay(3000);
    } else {
        Serial.println(" -> Sin riego. Rele APAGADO");
    }

    delay(2000);
}