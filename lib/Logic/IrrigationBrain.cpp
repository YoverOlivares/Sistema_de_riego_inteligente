#include "IrrigationBrain.h"
#include <Arduino.h>

// Instancia estática del motor de IA
static Eloquent::TinyML::TfLite<N_INPUTS, N_OUTPUTS, TENSOR_ARENA_SIZE> ml;

void IrrigationBrain::init() {
    Serial.print("[IA] Intentando cargar modelo de ");
    Serial.print(riego_model_len);
    Serial.println(" bytes...");

    // Intentamos iniciar. Si falla, begin() devuelve false.
    modeloCargado = ml.begin(riego_model);

    if (modeloCargado) {
        Serial.println("[IA] ✅ ÉXITO: Modelo cargado en memoria.");
    } else {
        Serial.println("[IA] ❌ ERROR CRÍTICO: Falló la carga del modelo.");
        Serial.println("[IA] Posibles causas: Tensor Arena muy pequeño o Array corrupto.");
    }
}

float IrrigationBrain::calcularRiego(ContextoAmbiental datos) {
    // PROTECCIÓN: Si el modelo no cargó, no intentamos predecir (evita el Crash)
    if (!modeloCargado) {
        Serial.println("[IA] FALLO: Usando respaldo Heurístico.");
        
        if (datos.humedadSuelo < 40.0) {
            return 10.0; // Regar 10 segundos si está seco
        } else {
            return 0.0;
        }
    }

    float entrada[3] = { 
        datos.humedadSuelo, 
        datos.temperaturaAire, 
        datos.humedadAire 
    };

    // Si llegamos aquí, es seguro predecir
    float prediccion = ml.predict(entrada);

    // Filtros de seguridad
    if (prediccion < 0) prediccion = 0;
    if (prediccion > 20) prediccion = 20;

    return prediccion;
}