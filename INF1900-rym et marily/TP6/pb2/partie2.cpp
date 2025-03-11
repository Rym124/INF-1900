#include <avr/io.h>
#define F_CPU 8000000
#include <util/delay.h>
#include <avr/interrupt.h>
#include "can.h"

// Rym Fortas et Marily Lemire

void allumeVert()
{
    PORTB &= ~(1 << PB0);
    PORTB |= (1 << PB1);
}

void initialisation(void){
    UBRR0H = 0;
    UBRR0L = 0xCF;
    UCSR0A &= ~((1<<RXC0) | (1<<TXC0));
    UCSR0B |=(1<< RXEN0) | (1<<TXEN0);
    UCSR0C |= (1<< UCSZ00)|(1 << UCSZ01);
}


void transmissionURAT(unsigned char donnee){
    while(!(UCSR0A &(1<< UDRE0)))
    ;
    UDR0 = donnee;
}


void allumeRouge()
{
    PORTB |= (1 << PB0);
    PORTB &= ~(1 << PB1);
}

void allumeAmbre()
{

        PORTB |= (1 << PB0);
        PORTB &= ~(1 << PB1);
        _delay_ms(5);
        PORTB |= (1 << PB1);
        PORTB &= ~(1 << PB0);
        _delay_ms(8);
    
    

}


int main(){



    initialisation();

    DDRB |= (1 << PB0) | (1 << PB1);
    DDRA &= ~(1 << PA0); 

    can convertisseur = can();


    while(true){

        uint16_t valeurAnalogique = convertisseur.lecture(PA0); // il faut lui donner la position de PA) qui est 0
        valeurAnalogique = valeurAnalogique >> 2;
        transmissionURAT(valeurAnalogique);
        

        if (valeurAnalogique > 250) { 
        allumeRouge(); 
        }

        else if(valeurAnalogique < 125) { 
        allumeVert(); 
        }
        
        else {
            allumeAmbre(); 
        }
        
    }

    
}
