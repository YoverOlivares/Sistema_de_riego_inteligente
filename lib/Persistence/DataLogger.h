#ifndef DATALOGGER_H
#define DATALOGGER_H

#include <Arduino.h>
#include "ContextoAmbiental.h"

class DataLogger {
  public:
    void init();
    void guardarLectura(ContextoAmbiental datos);
};

#endif