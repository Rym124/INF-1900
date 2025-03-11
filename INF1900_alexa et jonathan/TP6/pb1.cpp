#include <avr/io.h>
#define F_CPU 8000000
#include <util/delay.h>
#include <avr/interrupt.h>


enum class State {
    ETEINT,
    VERT1,
    ROUGE,
    VERT2
};

volatile uint8_t gMinuterieExpiree = 0;
volatile uint8_t gBoutonPoussoir = 0;
State currentState = State::ETEINT;
uint8_t compteur = 0; 

void turnRedLed() {
    PORTB |= (1 << PB0);  
    PORTB &= ~(1 << PB1); 
}

void turnGreenLedOn() {
    PORTB |= (1 << PB1);  
    PORTB &= ~(1 << PB0); 
}


void turnOffLeds() {
    PORTB &= ~((1 << PB0) | (1 << PB1)); // Turn off both LEDs
} 


void initialisation() {
    cli(); 
    DDRB |= (1 << PB0) | (1 << PB1);
    DDRD &= ~(1 << PD2);
    turnOffLeds();
    EIMSK |= (1 << INT0); 
    EICRA |= (1 << ISC00);
    sei(); 
}

ISR (TIMER1_COMPA_vect) {
    gMinuterieExpiree = 1;
    compteur+=10;

}


ISR(INT0_vect) {
    _delay_ms(30);
    if (!(PIND & (1 << PD2))) { 
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

int main() {
    initialisation();
    State currentState = State::ETEINT;
    uint16_t duree = calculDuree(F_CPU, 1024 , 1);
    
    while(true) {
        
        switch(currentState) {
            case State::ETEINT:
                if (gBoutonPoussoir == 1) {
                    currentState = State::VERT1;
                    partirMinuterie(duree);

                }
                break;

            case State::VERT1:
                if (gBoutonPoussoir == 0 || compteur == 120){
                    cli();
                    turnGreenLedOn();
                    _delay_ms(500);
                    turnOffLeds();
                    currentState = State::ROUGE;
                }
                break;

            case State::ROUGE:
                _delay_ms(2000);
                for (uint8_t i = 0; i < compteur/2 ; i++){
                        turnRedLed();
                        _delay_ms(100);
                        turnOffLeds();
                        _delay_ms(400);
                }
                currentState = State::VERT2;
                break;
            
            case State::VERT2:
                turnGreenLedOn();
                _delay_ms(1000);
                turnOffLeds();
                currentState = State::ETEINT;
                sei();
        }
        
    }

    
}
