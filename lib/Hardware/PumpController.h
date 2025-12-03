#ifndef PUMP_CONTROLLER_H
#define PUMP_CONTROLLER_H

#include <Arduino.h>

class PumpController {
  private:
    int pinRele;

  public:
    PumpController(int pin);
    void init();
    void activar(float segundos);
};

#endif  