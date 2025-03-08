#include <avr/io.h>
#include <util/delay.h>

class Debounce {
    public:
        // Constructeur
        Debounce(volatile uint8_t& pinReg, uint8_t pin, uint16_t debounceDelay);
        
        // Méthode de détection de l'état du bouton avec anti-rebond
        bool debounce();
        
    private:
    volatile uint8_t& pinReg;  // Registre de la pin
    uint8_t pin;               // Numéro de la pin
    uint16_t debounceDelay;    // Délai pour l'anti-rebond
};