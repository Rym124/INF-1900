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
#include "minuterie0.h"




uint16_t convertirPourcentage(uint16_t pourcentage, uint16_t valeurMax)
{
    return (pourcentage * valeurMax) / CONVERSION;
}

Minuterie0::Minuterie0(ModeMinuterie0 mode, uint16_t valeurCtc, uint16_t prescaler)
    :leMode_(mode), valeurCtc_(valeurCtc)
{
    prescaler_ = choisirPrescaler(prescaler);
    
    if (mode == ModeMinuterie0::CTC)
    {
        configurerCtc();
    }
    else if (mode == ModeMinuterie0::PWM)
    {
        configurerPwm();
    } 
   
} 

uint16_t Minuterie0::choisirPrescaler(uint16_t valeur)
{ 
    if (valeur == 1)
        return (1 << CS00);
    if (valeur == PRESCALER8)
        return (1 << CS01);
    if (valeur == PRESCALER64)
        return (1 << CS00) | (1 << CS01);
    if (valeur == PRESCALER256)
        return (1 << CS02);
    if (valeur == PRESCALER1024)
        return (1 << CS00) | (1 << CS02);

    return 0;
}

void Minuterie0::configurerPwm()
{ 
    TCCR0A = (1 << COM0A1) | (1 << COM0B1) | (1 << WGM00);
    TCCR0B = (1 << CS01);   
}

void Minuterie0::ajusterPwm(uint8_t dureeA, uint8_t dureeB)
{

    comparerSortiesRegistres(dureeA, dureeB);
    configurerPwm();
}

void Minuterie0::partirCompteur()
{
    TCCR0B |= prescaler_; 
}


void Minuterie0::arreterCompteur()
{
    TCCR0B &= ~((1 << CS02) | (1 << CS01) | (1 << CS00)); 
    TIMSK0 = 0;        
}

void Minuterie0::configurerCtc()
{ 
    TCNT0 = 0;
    TCCR0A |= (1 << WGM02);
    OCR0A = valeurCtc_;
}

void Minuterie0::comparerSortiesRegistres(uint16_t dureeA, uint16_t dureeB)
{
    OCR0A = dureeA; 
    OCR0B = dureeB;
}

void Minuterie0::activerInterruption()
{
    cli();
    TIMSK0 |= (1 << OCIE0A);
    sei();
}
