
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
Fichier cpp: Classe "Minuterie" pour la configuration 
et l'utilisation des minutries */ 


#define F_CPU 8000000
#define CONVERSION 100
#define PRESCALER8 8
#define PRESCALER64 64
#define PRESCALER256 256
#define PRESCALER1024 1024

#include <avr/io.h>
#include <util/delay.h>
#include "minuterie1.h"





uint16_t convertirPourcentage(uint16_t pourcentage, uint16_t valeurMax)
{
    return (pourcentage * valeurMax) / CONVERSION;
}

Minuterie1::Minuterie1(uint16_t valeurCtc, uint16_t prescaler)
    :  valeurCtc_(valeurCtc)
{
    prescaler_ = choisirPrescaler(prescaler);
}

uint16_t Minuterie1::choisirPrescaler(uint16_t valeur)
{       
    if (valeur == 1)
        return (1 << CS10);
    if (valeur == PRESCALER8)
        return (1 << CS11);
    if (valeur == PRESCALER64)
        return (1 << CS10) | (1 << CS11);
    if (valeur == PRESCALER256)
        return (1 << CS12);
    if (valeur == PRESCALER1024)
        return (1 << CS10) | (1 << CS12);
    return 0;

}

void Minuterie1::partirCompteur()
{ 
    

    TCNT1 = 0;
    OCR1A = valeurCtc_;
    TCCR1B |= (1 << WGM12)| prescaler_; 

    
}

void Minuterie1::arreterCompteur()
{
    TCCR1B &= ~((1 << CS12) | (1 << CS11) | (1 << CS10));
    TIMSK1 &= ~(1 << OCIE0A);
}


void Minuterie1::comparerSortiesRegistres(uint16_t dureeA)
{
    OCR1A = dureeA;
}

void Minuterie1::activerInterruption()
{
    cli();
    TIMSK1 |= (1 << OCIE1A);
    sei(); 
}