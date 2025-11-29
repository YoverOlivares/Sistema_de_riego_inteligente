#ifndef IRRIGATION_BRAIN_H
#define IRRIGATION_BRAIN_H

#include "ContextoAmbiental.h"

class IrrigationBrain {
  public:
    // Método principal de decisión
    float calcularRiego(ContextoAmbiental datos);
};

#endif