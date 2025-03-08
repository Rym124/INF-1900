#include "Debounce.hpp"

// Constructeur
Debounce::Debounce(volatile uint8_t& pinReg, uint8_t pin, uint16_t debounceDelay)
    : pinReg(pinReg), pin(pin), debounceDelay(debounceDelay) {}

// Méthode de détection de l'état du bouton avec anti-rebond
bool Debounce::isPressed() {
    if (pinReg & (1 << pin)) {
        _delay_ms(debounceDelay);  // Attendre un délai pour éviter le rebond
        return pinReg & (1 << pin);  // Vérifier à nouveau l'état du bouton
    }
    return false;  // Le bouton n'est pas pressé
}