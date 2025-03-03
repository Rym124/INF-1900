#include <avr/io.h>
#define F_CPU 8000000UL
#include <util/delay.h>
#include <avr/interrupt.h>
#include "can.h"

void turnRedLedOn() {
    PORTB |= (1 << PB0);  
    PORTB &= ~(1 << PB1); 
}

void turnGreenLedOn() {
    PORTB |= (1 << PB1);  
    PORTB &= ~(1 << PB0); 
}

void turnAmberLedOn() {
    turnGreenLedOn();
    _delay_ms(5);
    turnRedLedOn();
    _delay_ms(5);

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
        voltageConvertie = voltageConvertie >> 2;

        if (voltageConvertie >= 230 ) {
            turnRedLedOn();
        }
        else if (voltageConvertie <= 50) {
            turnGreenLedOn();
        }
        else {

            turnAmberLedOn();
            
        }
    
        //_delay_ms(5);
        transmissionUART(voltageConvertie);
      
    }


 
}
