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


Roues:: Roues( Minuterie2 minuterie, uint16_t vitesseDroite, uint16_t vitesseGauche) : minuterie_(minuterie), vitesseDroite_(0), vitesseGauche_(0){};


void Roues::avancer(Minuterie2 laMinuterie,  uint16_t vitesseDroite, uint16_t vitesseGauche)
{
    configurerMinuterie2();
    avancerPorts();
    laMinuterie.ajusterPwm(vitesseDroite, vitesseGauche);
}

void Roues::reculer(Minuterie2 laMinuterie,  uint16_t vitesseDroite, uint16_t vitesseGauche)
{
    configurerMinuterie2();
    reculerPorts();
    laMinuterie.ajusterPwm(vitesseDroite, vitesseGauche);
}

void Roues::tournerDroite(Minuterie2 laMinuterie, uint16_t vitesseGauche)
{
    configurerMinuterie2();
    avancerPorts();
    laMinuterie.ajusterPwm(0, vitesseGauche);
}

void Roues::tournerGauche(Minuterie2 laMinuterie, uint16_t vitesseDroite)
{
    configurerMinuterie2();
    avancerPorts();
    laMinuterie.ajusterPwm(vitesseDroite,0);
}

void Roues::arreter(Minuterie2 laMinuterie)
{
    configurerMinuterie2();
    laMinuterie.ajusterPwm(0, 0);
}

void Roues:: configurerMinuterie2()
{
    DDRD |=(1 << PD7)|(1 << PD6)| (1 << PD4) | (1 << PD5);
}


void Roues::reculerPorts()
{
    PORTD |=(1 << PD4) | (1 << PD5);
}

void Roues::avancerPorts()
{ 
    PORTD &= ~((1 << PD4) | (1 << PD5));
}