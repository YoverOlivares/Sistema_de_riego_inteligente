#pragma once
#include "ContextoAmbiental.h"
#include <EloquentTinyML.h> 
#include "modelo_entrenado.h"

// --- AJUSTES CRÍTICOS ---
#define N_INPUTS 3    
#define N_OUTPUTS 1   
// CAMBIO IMPORTANTE: Subimos de 4KB a 12KB para evitar el desbordamiento
# define TENSOR_ARENA_SIZE 10 * 1024 

class IrrigationBrain {
  public:
    void init();
    float calcularRiego(ContextoAmbiental datos);
    
  private:
    // Variable para saber si el cerebro está sano o muerto
    bool modeloCargado = false;
};