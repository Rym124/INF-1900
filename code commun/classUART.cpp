#include "classUART.h"
#include <stdio.h>
#include <stdlib.h>
#define TAILLE 10


UART::UART() {
    // Initialisation du UART pour une communication à 2400 bauds
    UBRR0H = 0;
    UBRR0L = 0xCF; //chiffre magique a enlever
    
    // Désactive les flags RXC et TXC
    UCSR0A &= ~((1 << RXC0) | (1 << TXC0));
    
    // Active la réception et la transmission
    UCSR0B |= (1 << RXEN0) | (1 << TXEN0);
    
    // Configure les trames: 8 bits de données, 1 bit de stop, pas de parité
    UCSR0C |= (1 << UCSZ01) | (1 << UCSZ00);
}

void UART::transmissionParOctet( char data) {
    // Attendre que le buffer de transmission soit vide
    while (!(UCSR0A & (1 << UDRE0))) ;
    
    // Mettre les données dans le registre UDR0 pour les envoyer
    UDR0 = data;
}
void UART::transmissionVariable(uint16_t valeur){
    char texte[TAILLE];
    snprintf(texte, TAILLE, "%d", valeur); 
    transmissionParBit(texte);
}

void UART::transmissionParBit(const  char* texte) {

    uint8_t longueur = 0;
    while (texte[longueur] != '\0') {
        longueur++;
    }

    for (uint8_t i = 0; i < longueur; i++){
        transmissionParOctet(texte[i]);
    }
    
}

