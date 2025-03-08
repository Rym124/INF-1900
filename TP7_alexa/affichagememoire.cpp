#include "affichagememoire.h"

UART::UART() {
    initialisation();
}

void UART::initialisation(void) {
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

void UART::transmission(unsigned char data) {
    // Attendre que le buffer de transmission soit vide
    while (!(UCSR0A & (1 << UDRE0))) ;
    
    // Mettre les données dans le registre UDR0 pour les envoyer
    UDR0 = data;
}
