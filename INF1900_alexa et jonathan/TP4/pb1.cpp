#include <avr/io.h>
#define F_CPU 8000000
#include <util/delay.h>
#include <avr/interrupt.h>

const uint8_t DELAY = 10;
const uint8_t AMBER_DELAY = 5;

enum class State {
    RED1, 
    AMBER, 
    GREEN1, 
    RED2, 
    OFF, 
    GREEN2
};


volatile State currentState = State::RED1;

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

void waitPress() {
    EICRA |= (1 << ISC01) | (1 << ISC00); 
}

void waitRelease() {
    EICRA |= (1 << ISC01); 
    EICRA &= ~(1 << ISC00);
}

ISR(INT0_vect) {
    _delay_ms(30); 
    switch (currentState) {
        case State::RED1:
        currentState = State::AMBER;
             waitRelease() ;
        break;

        case State::AMBER:   waitPress();

            currentState = State::GREEN1;
        break;

        case State::GREEN1:
             waitRelease() ;
                       
            currentState = State::RED2;
    
        break;

        case State::RED2:
                  waitPress();
            currentState = State::OFF;
    
        break;
        
        case State::OFF:
             waitRelease() ;
   
            currentState = State::GREEN2;
        break;
           
        case State::GREEN2:
                  waitPress();
    
       
            currentState = State::RED1;

        break;

    }
    EIFR |= (1 << INTF0); 
}



int main() {
    initialisation();
    currentState = State::RED1;
    

    while (true) {
        switch (currentState) {
            case State::RED1:
                turnRedLed(); 

                break;

            case State::AMBER:
        
                turnRedLed();
                _delay_ms(AMBER_DELAY);
                turnGreenLedOn();
                _delay_ms(AMBER_DELAY);
                // waitRelease();
            
                break;

            case State::GREEN1:
                turnGreenLedOn();
                break;

            case State::RED2:
                
                turnRedLed();
               
                break;
            
            case State::OFF:
                
                turnOffLeds();
                
                break;
            
            case State::GREEN2:
                
                turnGreenLedOn();

                break;
        }
    }
}