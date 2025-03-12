#include <avr/io.h>
#define F_CPU 8000000
#include <util/delay.h>

class DEL {
public:
    // Construit un gestionnaire de DEL avec les ports demandés
    DEL(uint8_t bornePositive, uint8_t borneNegative, volatile uint8_t* ddr, volatile uint8_t* port);
    
    // Construit un gestionnaire de DEL avec les ports PB1 (+) et PB0 (-)
    DEL();

    void allumerRouge();
    void allumerVert();
    void allumerAmbre();

    void eteindre();
    

    // Clignotement (Vert) en fonction de la durée (fréquence fixe à 2 Hz)
    void clignoterVert(uint16_t dureeMs);

    // Clignotement (Rouge) en fonction de la durée (fréquence fixe à 2 Hz)
    void clignoterRouge(uint16_t dureeMs);

    // Clignotement (Vert) en fonction du nombre et de la fréquence en Hz
    void clignoterVert(uint8_t nombreFois, uint16_t frequence);

    // Clignotement (Rouge) en fonction du nombre et de la fréquence en Hz
    void clignoterRouge(uint8_t nombreFois, uint16_t frequence);

private:
    uint8_t bornePositive_, borneNegative_;
    volatile uint8_t* port_, * ddr_;

    const static uint8_t DELAI_AMBRE_MS = 5;
    const static uint8_t FREQUENCE_CLIGNOTEMENT_HZ = 1;
};