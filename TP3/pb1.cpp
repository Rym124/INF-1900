#define F_CPU 8000000
#define freq 1000
#include <avr/io.h>
#include <util/delay.h>

void set_delay(uint16_t delay)
{
    while (delay--)
        _delay_ms(1);
}

void redLedOn()
{
    PORTA &= ~(1 << PA0);
    PORTA |= (1 << PA1);
}

void LedOff()
{
    PORTA &= ~(1 << PA0);
    PORTA &= ~(1 << PA1);
}

void fade_out()
{
    uint16_t total_duration = 3000; // Durée totale en microsecondes (3 secondes)
    uint16_t steps = 100;           // Nombre de steps pour la transition (de 100% à 0%)
    uint16_t a = 100;               // Intensité initiale à 100%

    // Calculer la durée de chaque pas (en microsecondes)
    uint16_t delay_per_step = total_duration / steps;

    // Effectuer une transition de 100% à 0% de luminosité
    for (uint16_t i = 0; i < steps; i++)
    {
        uint16_t redOn = (a * delay_per_step) / 100; // Durée d'allumage du LED pour chaque cycle
        uint16_t redOff = delay_per_step - redOn;    // Durée d'extinction du LED pour chaque cycle

        redLedOn();
        set_delay(redOn);
        LedOff();
        set_delay(redOff);

        // Réduire l'intensité (de 100% à 0%)
        a = 100 - i;
    }
}

int main()
{
    DDRA |= (1 << PA0) | (1 << PA1);

    while (1)
    {
        fade_out();      // Fade-out du LED // Allumer le LED à 100%
        set_delay(1000); // Petit délai entre chaque boucle
    }
}