#include <avr/io.h>
#define F_CPU 8000000
#include <util/delay.h>
#include <avr/interrupt.h>


volatile uint8_t gMinuterieExpiree = 0;
volatile uint8_t gBoutonPoussoir = 0;

void turnRedLed() {
    PORTA |= (1 << PA0);  
    PORTA &= ~(1 << PA1); 
}

void turnGreenLedOn() {
    PORTA |= (1 << PA1);  
    PORTA &= ~(1 << PA0); 
}

void turnOffLeds() {
    PORTA &= ~((1 << PA0) | (1 << PA1)); // Turn off both LEDs
}


void initialisation() {
    cli(); 
    DDRA |= (1 << PA0) | (1 << PA1); 
    PORTA &= ~((1 << PA0) | (1 << PA1)); 
    EIMSK |= (1 << INT0); 
    EICRA |= (1 << ISC01) | (1 << ISC00); 
    sei(); 
}

ISR (TIMER1_COMPA_vect) {
    gMinuterieExpiree = 1;

}


ISR(INT0_vect) {
    _delay_ms(30);
    if (PIND & (1 << PD2)) { 
        gBoutonPoussoir = 1;
    } else {
        gBoutonPoussoir = 0;
    }
    EIFR |= (1 << INTF0);
}

uint16_t calculDuree(uint32_t frequence , uint16_t prescaler , uint8_t periode){
    return ((frequence / prescaler) * periode - 1);
}



void partirMinuterie ( uint16_t duree ) {

    gMinuterieExpiree = 0;

    // mode CTC du timer 1 avec horloge divisée par 1024
    // interruption après la durée spécifiée

    TCNT1 = 0;

    OCR1A = duree; 

    TCCR1A |= (1 << COM1A0) | (1 << COM1B0);

    TCCR1B |= (1 << WGM12) | (1 << CS12) | (1 << CS10);

    TCCR1C = 0;

    TIMSK1 |= (1 << OCIE1A) ;


}
int main(){
    initialisation();
    _delay_ms(10000);
    for(uint8_t i = 0; i < 5; i++){
        turnRedLed();
        _delay_ms(25);
        turnOffLeds();
        _delay_ms(25);
    }

    uint16_t duree = calculDuree(F_CPU, 1024 , 1);
    partirMinuterie(duree);

    do {

    } while ( gMinuterieExpiree == 0 && gBoutonPoussoir == 0 );

    if(gMinuterieExpiree == 0 && gBoutonPoussoir == 1){
        turnGreenLedOn();
    }
    else {
        turnRedLed();
    }
    
    cli();


}