#include <avr/io.h>
#include <avr/interrupt.h>
#include "memoire_24.h"

void initialisationUART(void)
{

    // 2400 bauds. Nous vous donnons la valeur des deux

    // premiers registres pour vous éviter des complications.

    UBRR0H = 0;

    UBRR0L = 0xCF;

    // permettre la réception et la transmission par le UART0

    UCSR0A &= ~((1<<RXC0) | (1<<TXC0));

    UCSR0B = (1 << RXEN0) | (1 << TXEN0); // bits 1(RX receiver enabled) et 0(TX transmitter enabled)

    // Format des trames: 8 bits, 1 stop bits, sans parité

    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
}

// Du USART vers le PC

void transmissionUART(unsigned char donnee)
{

    while (!(UCSR0A & (1 << UDRE0)));

    UDR0 = donnee;
}

int main(){
    initialisationUART();
    Memoire24CXXX memoire = Memoire24CXXX();
    const uint16_t adresse = 0x0000;

    const char texte[] = "*P*O*L*Y*T*E*C*H*N*I*Q*U*E* *M*O*N*T*R*E*A*L*";  
    int longueur = sizeof(texte);
    // char aLire [longueur];

    memoire.ecriture(adresse, (uint8_t*) texte, longueur);  

    const uint16_t fin = 0xFFFF;
    uint16_t debut = 0x0000;
    unsigned char data;
    
    
    while(debut != fin){

        memoire.lecture(debut, &data);  // 
        debut++;
        transmissionUART(data);  // Transmission des données via UART
        
        
    }
    
}
