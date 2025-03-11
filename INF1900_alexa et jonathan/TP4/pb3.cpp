#include <avr/io.h>
#define F_CPU 8000000
#include <util/delay.h>


uint16_t calculpourcentage(uint16_t pourcentage, uint16_t top){
    return (pourcentage * top)/100;
}

void ajustementPwm( uint16_t dureeA , uint16_t dureeB) {

    // mise à un des sorties OC1A et OC1B sur comparaison
    // mise à un des sorties OC1A et OC1B sur comparaison

    // réussie en mode PWM 8 bits, phase correcte

    // et valeur de TOP fixe à 0xFF (mode #1 de la table 16-5

    // page 130 de la description technique du ATmega324PA)

    OCR1A = dureeA;

    OCR1B = dureeB;


    // division d'horloge par 8 - implique une fréquence de PWM fixe

    TCCR1A |= (1 << COM1A0) | (1 << COM1B0) | (1 << WGM10); //| (1 << COM1A0) | (1 << COM1B0) ;

    TCCR1B |= (1 << CS11) ;

    TCCR1C = 0;
}

void initialisation() { 
    DDRD |= (1 << PD4) | (1 << PD5); 

}

int main() {
    
    initialisation();
    
    while (true) {
        ajustementPwm(calculpourcentage(0, 255), calculpourcentage(0, 255));
        _delay_ms(2000);
        
        ajustementPwm(calculpourcentage(25, 255), calculpourcentage(25, 255));
        _delay_ms(2000);
        
        ajustementPwm(calculpourcentage(50, 255), calculpourcentage(50, 255));
        _delay_ms(2000);
        
        ajustementPwm(calculpourcentage(75, 255), calculpourcentage(75, 255));
        _delay_ms(2000);
        
        ajustementPwm(calculpourcentage(100, 255), calculpourcentage(100, 255));
        _delay_ms(2000);
    }
}

     