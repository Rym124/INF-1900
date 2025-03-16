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
#include "minuterie.h"


Minuterie::Minuterie(TypeMinuterie type, ModeMinuterie mode, uint16_t valeurCtc, uint16_t prescaler)
    : leType_(type), leMode_(mode), valeurCtc_(valeurCtc)
{
    prescaler_ = choisirPrescaler(prescaler);
    if (leType_ == MINUTERIE1)
    {
        leMode_ = CTC; 
    }
    else if (leType_ == MINUTERIE0 || leType_ == MINUTERIE2)
    {
        leMode_ = PWM; 
    }
    if (mode == CTC)
    {
        configurerCtc();
    }
    else if (mode == PWM)
    {
        configurerPwm();
    } 
}

TypeMinuterie Minuterie::accederType()
{
    return leType_;
}

uint16_t Minuterie::choisirPrescaler(uint16_t valeur)
{ 
    switch (leType_)
    {
        case MINUTERIE0:
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
            break;

        case MINUTERIE1:
            break;

        case MINUTERIE2:
            if (valeur == 1)
                return (1 << CS20);
            if (valeur == PRESCALER8)
                return (1 << CS21);
            if (valeur == PRESCALER64)
                return (1 << CS20) | (1 << CS21);
            if (valeur == PRESCALER256)
                return (1 << CS22);
            if (valeur == PRESCALER1024)
                return (1 << CS20) | (1 << CS22);
            break;
    }
    return 0;
}

void Minuterie::configurerPwm()
{ 
    switch (leType_)
    {
        case MINUTERIE0:
            TCCR0A = (1 << COM0A1) | (1 << COM0B1) | (1 << WGM00);
            TCCR0B = (1 << CS01);
            break;

        case MINUTERIE1:
            break;

        case MINUTERIE2:

            TCCR2A = (1 << COM2A1) | (1 << COM2B1) | (1 << WGM20);
            TCCR2B = (1 << CS21);
            break;
    }
}
void Minuterie::ajusterPwm(uint8_t dureeA, uint8_t dureeB)
{

    comparerSortiesRegistres(dureeA, dureeB);
    configurerPwm();
}

void Minuterie::partirCompteur()
{

    switch (leType_)
    {
        case MINUTERIE0:
            TCCR0B |= prescaler_; 
            break;

        case MINUTERIE1:
            TCNT1 = 0;
            TCCR1B |= prescaler_;
            break;

        case MINUTERIE2:
            TCCR2B |= prescaler_;
            break;
    }
}

void Minuterie::arreterCompteur()
{
    switch (leType_)
    {
        case MINUTERIE0:
            TCCR0B &= ~((1 << CS02) | (1 << CS01) | (1 << CS00)); 
            TIMSK0 = 0;
            break;

        case MINUTERIE1:
            TCCR1B &= ~((1 << CS12) | (1 << CS11) | (1 << CS10));
            TIMSK1 = 0;
            break;

        case MINUTERIE2:
            TCCR2B &= ~((1 << CS22) | (1 << CS21) | (1 << CS20));
            TIMSK2 = 0;
            break;
    }
}

void Minuterie::configurerCtc()
{ 
    switch (leType_)
    {
        case MINUTERIE0:
            TCNT0 = 0;
            TCCR0A = 0; 
            TCCR0A |= (1 << WGM01);
            OCR0A = valeurCtc_;
            break;

        case MINUTERIE1: 
            TCNT0 = 0;
            TCCR1B = 0;
            TCCR1B |= (1 << WGM12);
            OCR1A = valeurCtc_;
            break;

        case MINUTERIE2:
            TCNT2 = 0;
            TCCR2A = 0;
            TCCR2A |= (1 << WGM21);
            OCR2A = valeurCtc_;
            break;
    }
}

void Minuterie::comparerSortiesRegistres(uint16_t dureeA, uint16_t dureeB)
{
    switch (leType_)
    {
        case MINUTERIE0:
            OCR0A = dureeA; 
            OCR0B = dureeB;
            break;

        case MINUTERIE1:
            OCR1A = dureeA;
            break;

        case MINUTERIE2:
            OCR2A = dureeA; 
            OCR2B = dureeB;
            break;
    }
}

uint16_t Minuterie::convertirPourcentage(uint16_t pourcentage, uint16_t valeurMax)
{
    return (pourcentage * valeurMax) / CONVERSION;
}