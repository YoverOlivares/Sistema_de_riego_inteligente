#include "IrrigationBrain.h"
#include <Arduino.h> // Para funciones matemáticas si se necesitan

float IrrigationBrain::calcularRiego(ContextoAmbiental datos) {
    float tiempoRiego = 0.0;
    
    // --- LÓGICA HEURÍSTICA (Versión Sprint 1) ---
    // Esta lógica será reemplazada por TinyML en el Sprint 2
    
    const float UMBRAL_HUMEDAD = 40.0; // %

    if (datos.humedadSuelo < UMBRAL_HUMEDAD) {
        // Base de riego
        tiempoRiego = 5.0; 

        // Factor de corrección térmica:
        // Si hace más de 25°C, añadimos agua extra por evaporación
        if (datos.temperaturaAire > 25.0) {
            float diferencia = datos.temperaturaAire - 25.0;
            tiempoRiego += (diferencia * 0.5); // 0.5s por cada grado extra
        }

        // Límite de seguridad (nunca regar más de 15 segundos seguidos)
        if (tiempoRiego > 15.0) tiempoRiego = 15.0;
    }

    return tiempoRiego;
}