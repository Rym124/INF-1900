#include <avr/io.h>
#define F_CPU 8000000
#include <util/delay.h>
#include "classTimer.h"

void ajustementPwm( uint16_t dureeA , uint16_t dureeB) {

    // mise à un des sorties OC1A et OC1B sur comparaison
    // mise à un des sorties OC1A et OC1B sur comparaison

    // réussie en mode PWM 8 bits, phase correcte

    // et valeur de TOP fixe à 0xFF (mode #1 de la table 16-5

    // page 130 de la description technique du ATmega324PA)

    OCR1A = dureeA;

    OCR1B = dureeB;


    // division d'horloge par 8 - implique une fréquence de PWM fixe

    TCCR1A |= (1 << COM1A0) | (1 << COM1B0) | (1 << WGM10); //| (1 << COM1A0) | (1 << COM1B0) ;

    TCCR1B |= (1 << CS11) ;

    TCCR1C = 0;
}


void partirMinuterie(uint16_t duree)  //il faut qu'il soit capable de choisir un prescaler
{

    gMinuterieExpiree = 0;

    // mode CTC du timer 1 avec horloge divisée par 1024

    // interruption après la durée spécifiée

    TCNT1 = 0;

    OCR1A = duree;

    TCCR1A = 0;

    TCCR1B = (1 << WGM12) | (1 << CS12) | (1 << CS10); // ctc prescaler 1024

    TCCR1C = 0;

    TIMSK1 = (1 << OCIE1A);
}

// choisir un prescaler :
