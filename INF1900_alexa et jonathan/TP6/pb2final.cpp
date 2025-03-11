/*###############   Auteurs  #####################
########         TP2 Problème 1           ########
#####                                        #####
#####        Produit et ecrit par:           #####
#####        Alexa Kassar (2350528)          #####
#####        Jonathan Volcy (2383299)        #####
#####           INF1900 (groupe 03)          #####
#####                2025                    #####
##################################################

############## Broches(I/O) ####################
OUTPUT: PIN B1 et PIN B0 
PIN B0 is connected to the positive(+) post
PIN B1 is connected to the negative(-) post

############## Description #####################
Changement de la couleur de la DEL en fonction de l'intensité de la lumière.
lumière basse:couleur verte.
Lumière ambiante: couleur ambrée.
Lumière forte: couleur rouge.*/


#include <avr/io.h>
#define F_CPU 8000000UL
#include <util/delay.h>
#include <avr/interrupt.h>
#include "can.h"

#define HAUT_VOLTAGE 230
#define BAS_VOLTAGE 50
#define DELAY 5
#define DECALAGE 2

void allumerRouge() {
    PORTB |= (1 << PB0);  
    PORTB &= ~(1 << PB1); 
}

void allumerVert() {
    PORTB |= (1 << PB1);  
    PORTB &= ~(1 << PB0); 
}

void allumerAmbre() {
    turnGreenLedOn();
    _delay_ms(DELAY);
    turnRedLedOn();
    _delay_ms(DELAY);

}

void initialisationUART ( void ) {

    // 2400 bauds. Nous vous donnons la valeur des deux

    // premiers registres pour vous éviter des complications.

    UBRR0H = 0;

    UBRR0L = 0xCF;

    // permettre la réception et la transmission par le UART0

    UCSR0A &= ~((1 << RXC0) | (1 << TXC0));

    UCSR0B |= (1 << RXEN0) | (1 << TXEN0);

    // Format des trames: 8 bits, 1 stop bits, sans parité

    UCSR0C |= (1 << UCSZ01) | (1 << UCSZ00); 

}



void transmissionUART( unsigned char data ) 
{ 
    
    while ( !( UCSR0A & (1<<UDRE0)) ) ; 
    UDR0 = data; 

}

int main() {
    initialisationUART();
    DDRB |= (1 << PB0) | (1 << PB1);
    DDRA &= ~(1 << PA0);
    can convertisseurAN;
    

    while(true) {

        uint16_t voltageConvertie = convertisseurAN.lecture(0);
        voltageConvertie = voltageConvertie >> DECALAGE;

        if (voltageConvertie >= HAUT_VOLTAGE ) {
            turnRedLedOn();
        }
        else if (voltageConvertie <= BAS_VOLTAGE) {
            turnGreenLedOn();
        }
        else {

            turnAmberLedOn();
            
        }
    
        transmissionUART(voltageConvertie);
      
    }

}
