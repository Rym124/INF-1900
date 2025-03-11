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
INPUT: D2 connected to the push button 
OUTPUT: PIN A1 et PIN A0 
PIN A0 is connected to the positive(+) post
PIN A1 is connected to the negative(-) post

############## Description #####################
La DEL est éteinte au départ. 
Après trois appuis-relâchements du bouton, 
elle devient verte pendant 2 secondes, 
puis s'éteint et le cycle recommence.


##############    State Table   ################
 +---------------+-------+------------+-----------------+
| Present state | Input | Next state | DEL             |
+---------------+-------+------------+-----------------+
| INIT          | 0     | INIT       | OFF             |
| INIT          | 1     | PRESS1     | OFF             |
| PRESS1        | 0     | PRESS1     | OFF             |
| PRESS1        | 1     | PRESS2     | OFF             |
| PRESS2        | 0     | PRESS2     | OFF             |
| PRESS2        | 1     | ON         | OFF             |
| ON            | 0     | INIT       | GREEN(2seconds) |
| ON            | 1     | ON         | GREEN(2seconds) |
+---------------+-------+------------+-----------------+*/

#include <avr/io.h>
#define F_CPU 8000000
#include <util/delay.h>

const uint8_t DEBOUNCE_DELAY = 10;
const int LED_DELAY = 2000;

bool debounceD2() {
    if (PIND & (1 << PD2)) {
        _delay_ms(DEBOUNCE_DELAY);
        return PIND & (1 << PD2);
    }
    else {
        return false;
    }
}

void turnLedOff() {
    PORTA &= ~((1 << PA1) | (1 << PA0));
}

enum class State { 
    INIT, 
    PRESS1, 
    PRESS2, 
    ON
    };


int main() {
    State currentState = State::INIT;
    DDRA |= (1 << PA1)|(1<< PA0);
    DDRD &= ~(1<<PD2);

    while (true){
        switch (currentState) {
            case State::INIT:
                turnLedOff(); 
                if (debounceD2()){
                    while (debounceD2());
                    currentState = State::PRESS1;
                }
                else {
                    currentState = State::INIT;
                }
                break;
        
            case State::PRESS1:
                if (debounceD2()){ 
                    while (debounceD2());
                    currentState = State::PRESS2;
                }
                else {
                    currentState = State::PRESS1;
                }
                break;
            
            case State::PRESS2:
                if (debounceD2()){
                    while (debounceD2());
                    currentState = State::ON;
                }
                else {
                    currentState = State::PRESS2;
                }
                break;
    
            case State::ON:
                while(debounceD2());
                PORTA |= (1 << PA1);
                _delay_ms(LED_DELAY); 
                turnLedOff(); 
                currentState = State::INIT;
            break;
        }
    }
}
