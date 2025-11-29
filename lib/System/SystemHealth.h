#ifndef SYSTEM_HEALTH_H
#define SYSTEM_HEALTH_H

class SystemHealth {
  public:
    bool verificarSensores();
    float obtenerBateria();
};

#endif