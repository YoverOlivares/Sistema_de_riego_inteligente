#ifndef CONTEXTO_AMBIENTAL_H
#define CONTEXTO_AMBIENTAL_H

// Estructura que viaja entre las capas del sistema
struct ContextoAmbiental {
    // --- Entradas (Inputs) ---
    float humedadSuelo;    // 0.0 a 100.0 %
    float temperaturaAire; // °C
    float humedadAire;     // %
    
    // --- Salidas (Outputs) ---
    float tiempoRiegoCalculado; // Segundos (0 si no se debe regar)
    
    // Futuro: Timestamp, NivelBateria, etc.
};

#endif