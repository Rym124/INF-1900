#include <avr/io.h>
#define F_CPU 8000000
#include <util/delay.h>
#include "classTimer.h"
#include "classMoteur.h"


Moteurs:: Moteurs( Timers timer, uint16_t vitesseD, uint16t vitesseG) : timer(timer), vitesseD(0), vitesseG(0){};


void Moteurs::avancer(Timers leTimer,  uint16t vitesseD, uint16t vitesseG){
    configuration();
    portAvance();
    leTimer.ajustementPwm(vitesseD, vitesseG);
}

void Moteurs::reculer(Timers leTimer,  uint16t vitesseD, uint16t vitesseG){
    configuration();
    portRecule();
    leTimer.ajustementPwm(vitesseD, vitesseG);
}
void Moteurs::tournerDroite(Timers leTimer, uint16t vitesseG){
    configuration();
    portAvance();
    leTimer.ajustementPwm(0, vitesseG_);
}

void Moteurs::tournerGauche(Timers leTimer, uint16t vitesseD){
    configuration();
    portAvance();
    leTimer.ajustementPwm(vitesseD,0);
}
void Moteurs::arretRoue(Timers leTimer){
    configuration();
    leTimer.ajustementPwm(0, 0);
}

void Moteurs:: configuration(){
    switch (timer.getType())
    {
        case TIMER0:
        DDRB |= (1 << PB2) | (1 << PB3) | (1 << PB4) | (1 << PB5);
        break;

        case TIMER2:
        DDRD |=(1 << PD7)|(1 << PD6)| (1 << PD4) | (1 << PD5);
        break;
    }

}

void Moteurs::portRecule(){
    switch (timer.getType())
    {
        case TIMER0:
        PORTB |= (1 << PB2) | (1 << PB5);
        break;
        case TIMER2:
        PORTD |=(1 << PD2) | (1 << PD5);
        break;
    }

}
void Moteurs::portAvance(){
    switch (timer.getType()){
        case TIMER0:
        PORTB &= ~((1 << PB4) | (1 << PB5));
        break;
        case TIMER2:
        PORTD &= ~((1 << PD4) | (1 << PD5));
        break;
    }

}