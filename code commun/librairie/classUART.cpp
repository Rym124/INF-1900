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
Fichier cpp: Classe "TransmissionUart" pour la communication RS232 */

#define F_CPU 8000000
#define TAILLE 10
#define VITESSE 0xCF
#define DELAI 5

#include <avr/io.h>
#include <stdio.h>
#include <stdlib.h>
#include <util/delay.h>
#include "classUART.h"



TransmissionUart::TransmissionUart()
{
    UBRR0H = 0;
    UBRR0L = VITESSE; 
    UCSR0A &= ~((1 << RXC0) | (1 << TXC0));
    UCSR0B |= (1 << RXEN0) | (1 << TXEN0);
    UCSR0C |= (1 << UCSZ01) | (1 << UCSZ00);
}

void TransmissionUart::transmettreChar( char lettre) 
{
    while (!(UCSR0A & (1 << UDRE0))) ;
    UDR0 = lettre;
}

void TransmissionUart::transmettreEntier(uint16_t valeur)
{
    char texte[TAILLE];
    snprintf(texte, TAILLE, "%d", valeur); 
    transmettreString(texte);
}

void TransmissionUart::transmettreString(char* texte) 
{ 
    static uint8_t longueur = 0;
    while (texte[longueur] != '\0') 
    {
        longueur++;
    }

    for (uint8_t i = 0; i < longueur; i++)
    {
        transmettreChar(texte[i]);
        _delay_ms(DELAI);
    }
}

