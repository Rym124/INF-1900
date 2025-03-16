/*###############   Auteurs  #####################
########   TP7 et TP8 classe du Bouton    ########
#####                                        #####
#####        Produit et ecrit par:           #####
0#####           Equipe 5556                 #####
#####        Alexa Kassar (2350528)          #####
#####        Jonathan Volcy (2383299)        #####
#####       Rym Fortas (2385101)             #####
#####        Marily  Lemire (2350146)        #####
#####           INF1900 (groupe 03)          #####
#####                2025                    #####
##################################################


############## Description #####################
Fichier cpp: Classe "Roues" pour la configuration 
et l'utilisation des roues */ 

#define F_CPU 8000000

#include <avr/io.h>
#include <util/delay.h>
#include "minuterie.h"
#include "roues.h"


Roues:: Roues( Minuterie minuterie, uint16_t vitesseDroite, uint16_t vitesseGauche) : minuterie_(minuterie), vitesseDroite_(0), vitesseGauche_(0){};


void Roues::avancer(Minuterie laMinuterie,  uint16_t vitesseDroite, uint16_t vitesseGauche)
{
    configurer();
    avancerPorts();
    laMinuterie.ajusterPwm(vitesseDroite, vitesseGauche);
}

void Roues::reculer(Minuterie laMinuterie,  uint16_t vitesseDroite, uint16_t vitesseGauche)
{
    configurer();
    reculerPorts();
    laMinuterie.ajusterPwm(vitesseDroite, vitesseGauche);
}

void Roues::tournerDroite(Minuterie laMinuterie, uint16_t vitesseGauche)
{
    configurer();
    avancerPorts();
    laMinuterie.ajusterPwm(0, vitesseGauche);
}

void Roues::tournerGauche(Minuterie laMinuterie, uint16_t vitesseDroite)
{
    configurer();
    avancerPorts();
    laMinuterie.ajusterPwm(vitesseDroite,0);
}

void Roues::arreter(Minuterie laMinuterie)
{
    configurer();
    laMinuterie.ajusterPwm(0, 0);
}

void Roues:: configurer()
{
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

void Roues::reculerPrts()
{
    switch (minuterie_.accederType())
    {
        case MINUTERIE0:
            PORTB |= (1 << PB2) | (1 << PB5);
            break;

        case MINUTERIE2:
            PORTD |=(1 << PD4) | (1 << PD5);
            break;

        default: 
            break;
    }

}

void Roues::avancerPorts()
{
    switch (minuterie_.accederType())
    {
        case MINUTERIE0:
            PORTB &= ~((1 << PB2) | (1 << PB5));
            break;

        case MINUTERIE2:
            PORTD &= ~((1 << PD4) | (1 << PD5));
            break;

        default: 
            break;
    }

}