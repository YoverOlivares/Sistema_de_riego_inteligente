#include "PumpController.h"

PumpController::PumpController(int pin) {
    this->pinRele = pin;
}

void PumpController::init() {
    pinMode(pinRele, OUTPUT);
    digitalWrite(pinRele, LOW);
}

void PumpController::activar(float segundos) {
    if (segundos <= 0) return;

    Serial.print("[ACTUADOR] Regando durante ");
    Serial.print(segundos);
    Serial.println(" segundos...");

    digitalWrite(pinRele, HIGH);
    delay(segundos * 1000);
    digitalWrite(pinRele, LOW);
}