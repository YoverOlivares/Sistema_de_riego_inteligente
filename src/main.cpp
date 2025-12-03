#include <Arduino.h>
#include "ContextoAmbiental.h"
#include "SensorManager.h"
#include "PumpController.h"
#include "IrrigationBrain.h"
#include "DataLogger.h"
#include "SystemHealth.h"

// --- Definición de Pines de Hardware ---
#define PIN_DHT 15
#define PIN_SUELO 34
#define PIN_RELE 26

// --- Inyección de Dependencias (Instanciación) ---
SensorManager sensores(PIN_SUELO, PIN_DHT);
PumpController bomba(PIN_RELE);
IrrigationBrain cerebro;
DataLogger logger;
SystemHealth monitor;

void setup() {
    Serial.begin(115200);
    // Esperar un momento a que el serial estabilice
    delay(1000);
    Serial.println("\n>>> INICIANDO SISTEMA DE RIEGO IOT (SPRINT 1) <<<");

    // Inicializar submódulos
    sensores.init();
    bomba.init();
    logger.init();

    // --- ESTA LÍNEA ES CRÍTICA ---
    cerebro.init(); 
    // -----------------------------

    Serial.println(">>> Sistema listo y esperando ciclo...");
}

void loop() {
    // 1. Verificar Salud del Sistema
    if (!monitor.verificarSensores()) {
        Serial.println("ERROR CRÍTICO: Fallo en sensores. Reintentando...");
        delay(5000);
        return;
    }

    // 2. Adquisición de Datos (Capa Hardware)
    ContextoAmbiental ctx = sensores.leerSensores();

    // 3. Inferencia / Decisión (Capa Lógica)
    ctx.tiempoRiegoCalculado = cerebro.calcularRiego(ctx);

    // 4. Persistencia y Telemetría (Capa Datos)
    // Esto imprime la línea CSV en el monitor serial
    logger.guardarLectura(ctx); 

    // 5. Actuación (Capa Hardware)
    if (ctx.tiempoRiegoCalculado > 1.0) {
        bomba.activar(ctx.tiempoRiegoCalculado);
        Serial.println(" -> Ciclo de riego finalizado.");
    } else {
        // Opcional: Feedback visual de "No Riego"
        // Serial.println(" -> Condiciones óptimas. No se requiere riego.");
    }

    // 6. Espera (Intervalo de Muestreo)
    // Para recolección de datos acelerada, usamos 2 segundos.
    // En producción real, esto sería deepSleep de 30 minutos.
    delay(2000); 
}