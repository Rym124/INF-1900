
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
#include "minuterie2.h"

Minuterie2::Minuterie2(ModeMinuterie2 mode,  uint16_t valeurCtc, uint16_t prescaler)
    : leMode_(mode), valeurCtc_(valeurCtc)
{
    prescaler_ = choisirPrescaler(prescaler);
    switch(leMode_){
        case ModeMinuterie2::CTC:
            configurerCtc();
            break;

        case ModeMinuterie2::PWM:
            configurerPwm();
            break;
    } 
    
}


uint16_t Minuterie2::choisirPrescaler(uint16_t valeur)
{ 
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
    return 0;    
}

void Minuterie2::configurerPwm()
{ 
    TCCR2A |= (1 << COM2A1) | (1 << COM2B1) | (1 << WGM20);
    TCCR2B |= (1 << CS21);         
}

void Minuterie2::ajusterPwm(uint8_t dureeA, uint8_t dureeB)
{
    comparerSortiesRegistres(dureeA, dureeB);
    configurerPwm();
}

void Minuterie2::partirCompteur()
{
    TCCR2B |= prescaler_;
}

void Minuterie2::arreterCompteur()
{
    TCCR2B &= ~((1 << CS22) | (1 << CS21) | (1 << CS20));
    TIMSK2 = 0;
}

void Minuterie2::configurerCtc()
{ 
    TCNT2 = 0;
    TCCR2B = 0;
    TCCR2A |= (1 << WGM22);
    OCR2A = valeurCtc_;
            
}

void Minuterie2::comparerSortiesRegistres(uint16_t dureeA, uint16_t dureeB)
{
    OCR2A = dureeA; 
    OCR2B = dureeB; 
}
void Minuterie2::activerInterruption()
{
    cli();
    TIMSK2 |= (1 << OCIE2A);
    sei(); 
}

void Minuterie2::configurerMinuterie2()
{
    DDRD |=(1 << PD7)|(1 << PD6)| (1 << PD4) | (1 << PD5);
}

uint16_t Minuterie2::convertirPourcentage(uint16_t pourcentage, uint16_t valeurMax)
{
    return (pourcentage * valeurMax) / CONVERSION;
}
