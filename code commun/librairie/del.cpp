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
Fichier cpp: Classe "Del" pour l'utilisation et
le fonctionnement de la Del*/

#define CONVERSION 1000
#define DEMI_PERIODE 2

#include "del.h"

void delaiMs(uint16_t delai) 
{
    for(uint16_t i = 0; i < delai; i++) 
    {
        _delay_ms(1);
    }
}

Del::Del(uint8_t bornePositive, uint8_t borneNegative, volatile uint8_t* ddr, volatile uint8_t* port) : 

    bornePositive_(bornePositive), borneNegative_(borneNegative), port_(port), ddr_(ddr) 
{
    *ddr |= (1 << bornePositive_) | (1 << borneNegative_);
}

Del::Del() : bornePositive_(PB1), borneNegative_(PB0), port_(&PORTB), ddr_(&DDRB) 
{
    *ddr_ |= (1 << bornePositive_) | (1 << borneNegative_);
}

void Del::allumerRouge() 
{
    *port_ |= (1 << bornePositive_);
    *port_ &= ~(1 << borneNegative_);
}

void Del::allumerVert() 
{
    *port_ &= ~(1 << bornePositive_);
    *port_ |= (1 << borneNegative_);
}

void Del::allumerAmbre() 
{
    allumerRouge();
    _delay_ms(DELAI_AMBRE_MS);
    allumerVert();
    _delay_ms(DELAI_AMBRE_MS);
}

void Del::eteindre() 
{
    *port_ &= ~(1 << bornePositive_);
    *port_ &= ~(1 << borneNegative_);
}

void Del::clignoterVert(uint16_t dureeMs) 
{
    uint16_t nombreFois = FREQUENCE_CLIGNOTEMENT_HZ * dureeMs / CONVERSION;
    clignoterVert(nombreFois, FREQUENCE_CLIGNOTEMENT_HZ);
}

void Del::clignoterRouge(uint16_t dureeMs) 
{
    uint16_t nombreFois = FREQUENCE_CLIGNOTEMENT_HZ * dureeMs / CONVERSION;
    clignoterRouge(nombreFois, FREQUENCE_CLIGNOTEMENT_HZ);
}

void Del::clignoterVert(uint8_t nombreFois, uint16_t frequence)
{
    uint16_t periode_ms = CONVERSION / frequence;
    for (uint16_t i = 0; i < nombreFois; i++) 
    {
        allumerVert();
        delaiMs(periode_ms/DEMI_PERIODE);
        eteindre();
        delaiMs(periode_ms/DEMI_PERIODE);
    }
}

void Del::clignoterRouge(uint8_t nombreFois, uint16_t frequence) 
{
    uint16_t periode_ms = CONVERSION / frequence;
    for (uint8_t i = 0; i < nombreFois; i++) 
    {
        allumerRouge();
        delaiMs(periode_ms/DEMI_PERIODE);
        eteindre();
        delaiMs(periode_ms/DEMI_PERIODE);
    }
}