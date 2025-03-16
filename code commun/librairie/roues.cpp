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
#include "roues.h"


Roues:: Roues( Minuterie2 minuterie) : minuterie_(minuterie){};


void Roues::avancer(uint16_t vitesseDroite, uint16_t vitesseGauche)
{
    minuterie_.configurerMinuterie2();
    avancerPorts();
    minuterie_.ajusterPwm(vitesseDroite, vitesseGauche);
}

void Roues::reculer(uint16_t vitesseDroite, uint16_t vitesseGauche)
{
    minuterie_.configurerMinuterie2();
    reculerPorts();
    minuterie_.ajusterPwm(vitesseDroite, vitesseGauche);
}

void Roues::tournerDroite( uint16_t vitesseGauche)
{
    minuterie_.configurerMinuterie2();
    avancerPorts();
    minuterie_.ajusterPwm(0, vitesseGauche);
}

void Roues::tournerGauche( uint16_t vitesseDroite)
{
    minuterie_.configurerMinuterie2();
    avancerPorts();
    minuterie_.ajusterPwm(vitesseDroite,0);
}

void Roues::arreter()
{
    minuterie_.configurerMinuterie2();
    minuterie_.ajusterPwm(0, 0);
}

void Roues::reculerPorts()
{
    PORTD |=(1 << PD4) | (1 << PD5);
}

void Roues::avancerPorts()
{ 
    PORTD &= ~((1 << PD4) | (1 << PD5));
}
