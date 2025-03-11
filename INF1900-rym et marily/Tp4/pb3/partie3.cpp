#define F_CPU 8000000
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

void ajustementPwm(uint8_t dutyA, uint8_t dutyB)
{

    // mise à un des sorties OC1A et OC1B sur comparaison

    // réussie en mode PWM 8 bits, phase correcte

    // et valeur de TOP fixe à 0xFF (mode #1 de la table 16-5

    // page 130 de la description technique du ATmega324PA)

    OCR1A = (dutyA / 100.0) * 255; // gauche

    OCR1B = (dutyB / 100.0) * 255; // droite

    // division d'horloge par 8 - implique une fréquence de PWM fixe

    TCCR1A = (1 << COM1A1) | (1 << COM1B1) | (1 << WGM10);

    TCCR1B = (1 << CS11);

    TCCR1C = 0;
}

void initialisation(void)
{
    DDRD |= (1 << PD4) | (1 << PD5);
    DDRD |= (1 << PD7) | (1 << PD6);
}

int main()
{
    initialisation();

    uint8_t dutyCycles[] = {0, 25, 50, 75, 100};

    while (1)
    {
        for (uint8_t i = 0; i < 5; i++)
        {
            ajustementPwm(dutyCycles[i], dutyCycles[i]);
            _delay_ms(2000);
        }
    }
}
