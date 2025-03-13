#include "classUART.h"
#include <stdio.h>
#include <stdlib.h>

#define TAILLE 10


UART::UART() {

    UBRR0H = 0;
    UBRR0L = 0xCF; 
    UCSR0A &= ~((1 << RXC0) | (1 << TXC0));
    UCSR0B |= (1 << RXEN0) | (1 << TXEN0);
    UCSR0C |= (1 << UCSZ01) | (1 << UCSZ00);
}

void UART::transmissionParOctet( char data) {
    
    while (!(UCSR0A & (1 << UDRE0))) ;
    UDR0 = data;
}

void UART::transmissionVariable(uint16_t valeur){
    char texte[TAILLE];
    snprintf(texte, TAILLE, "%d", valeur); 
    transmissionParBit(texte);
}

void UART::transmissionParBit(char* texte) { //transmissionnsstring

    static uint8_t longueur = 0;
    while (texte[longueur] != '\0') {
        longueur++;
    }

    for (uint8_t i = 0; i < longueur; i++){
        transmissionParOctet(texte[i]);
        _delay_ms(5);
    }
}

