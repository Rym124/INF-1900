#define F_CPU 8000000

#include <avr/io.h>
#include <util/delay.h>
#include "minuterie.h"
#include "roues.h"


Roues:: Roues( Minuterie minuterie, uint16_t vitesseDroite, uint16_t vitesseGauche) : minuterie_(minuterie), vitesseDroite_(0), vitesseGauche_(0){};


void Roues::avancer(Minuterie laMinuterie,  uint16_t vitesseDroite, uint16_t vitesseGauche){
    configuration();
    portAvance();
    laMinuterie.ajustementPwm(vitesseDroite, vitesseGauche);
}

void Roues::reculer(Minuterie laMinuterie,  uint16_t vitesseDroite, uint16_t vitesseGauche){
    configuration();
    portRecule();
    laMinuterie.ajustementPwm(vitesseDroite, vitesseGauche);
}

void Roues::tournerDroite(Minuterie laMinuterie, uint16_t vitesseGauche){
    configuration();
    portAvance();
    laMinuterie.ajustementPwm(0, vitesseGauche);
}

void Roues::tournerGauche(Minuterie laMinuterie, uint16_t vitesseDroite){
    configuration();
    portAvance();
    laMinuterie.ajustementPwm(vitesseDroite,0);
}

void Roues::arretRoue(Minuterie laMinuterie){
    configuration();
    laMinuterie.ajustementPwm(0, 0);
}

void Roues:: configuration(){
    switch (minuterie_.accederType())
    {
        case MINUTERIE0:
            DDRB |= (1 << PB2) | (1 << PB3) | (1 << PB4) | (1 << PB5);
            break;

        case MINUTERIE2:
            DDRD |=(1 << PD7)|(1 << PD6)| (1 << PD4) | (1 << PD5);
            break;

        default: 
            break;
    }

}

void Roues::portRecule(){
    switch (minuterie_.accederType())
    {
        case MINUTERIE0:
            PORTB |= (1 << PB2) | (1 << PB5);
            break;

        case MINUTERIE2:
            PORTD |=(1 << PD2) | (1 << PD5);
            break;

        default: 
            break;
    }

}

void Roues::portAvance(){
    switch (minuterie_.accederType()){
        case MINUTERIE0:
            PORTB &= ~((1 << PB4) | (1 << PB5));
            break;
        case MINUTERIE2:
            PORTD &= ~((1 << PD4) | (1 << PD5));
            break;
        default: 
            break;
    }

}