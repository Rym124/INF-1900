/*###############   Auteurs  #####################
########         TP2 Problème 2           ########
#####                                        #####
#####        Produit et ecrit par:           #####
#####        Alexa Kassar (2350528)          #####
#####        Jonathan Volcy (2383299)        #####
#####           INF1900 (groupe 03)          #####
#####                2025                    #####
##################################################

############## Broches(I/O) ####################
INPUT: PIN D2 connected to the push button 
OUTPUT: PIN A1 et PIN A0 
PIN A0 is connected to the positive(+) post
PIN A1 is connected to the negative(-) post

############## Description #####################
La DEL commence en rouge au démarrage. Lors de l'appui sur le bouton-poussoir, elle devient ambre.
Quand le bouton est relâché, elle devient verte. Un nouvel appui la remet en rouge, puis elle s'éteint en relâchant. 
Un dernier appui la rend verte, et en la relâchant, elle retourne au rouge pour recommencer le cycle.

###############   State Table   ################
+---------------+------------------------+------------+-------+
| Present state | Input(bouton poussoir) | Next state | DEL   |
+---------------+------------------------+------------+-------+
| RED1          | 0                      | RED1       | RED   |
| RED1          | 1                      | AMBER      | RED   |
| AMBER         | 0                      | GREEN1     | AMBER |
| AMBER         | 1                      | AMBER      | AMBER |
| GREEN1        | 0                      | GREEN1     | GREEN |
| GREEN1        | 1                      | RED2       | GREEN |
| RED2          | 0                      | OFF        | RED   |
| RED2          | 1                      | RED2       | RED   |
| OFF           | 0                      | OFF        | OFF   |
| OFF           | 1                      | GREEN2     | OFF   |
| GREEN2        | 0                      | RED1       | GREEN |
| GREEN2        | 1                      | GREEN2     | GREEN |
+---------------+------------------------+------------+-------+*/

#include <avr/io.h>
#define F_CPU 8000000
#include <util/delay.h>

const uint8_t DELAY = 10;
const uint8_t AMBER_DELAY = 5;

bool debounceD2(){
    if (PIND & (1 << PD2)) {
        _delay_ms(DELAY);
        return PIND & (1 << PD2);
    }
    else {
        return false;
    }
    
}

enum class State {
    RED1, 
    AMBER, 
    GREEN1, 
    RED2, 
    OFF, 
    GREEN2
};


void turnRedLed(){
    PORTA |= (1 << PA0);
    PORTA &= ~(1 << PA1);
}
void turnGreenLedOn(){
    PORTA |= (1 << PA1); 
    PORTA &= ~(1 << PA0); 
}

int main () {
    
    DDRA |= (1 << PA0) | (1 << PA1);
        
    State currentState = State::RED1;

    while (true) {

        switch (currentState){
        case State::RED1:
            turnRedLed();
            if (debounceD2()) {
                currentState = State::AMBER;
            }
            break;

        case State::AMBER:
            while(debounceD2()) {
                turnRedLed();
                _delay_ms(AMBER_DELAY);
                turnGreenLedOn();
                _delay_ms(AMBER_DELAY);
            }
            currentState = State::GREEN1;
            break;

        case State::GREEN1:
            turnGreenLedOn();
            if (debounceD2()) {
                currentState = State::RED2;
            }
            break;

        case State::RED2:
            turnRedLed();
            while (debounceD2());
            currentState = State::OFF;
            break;
        
        case State::OFF:
            PORTA &= ~((1 << PA1) | (1 << PA0));
            if (debounceD2()) {
                currentState = State::GREEN2;
            }
            break;
        
        case State::GREEN2:
            turnGreenLedOn();
            while (debounceD2());
            currentState = State::RED1;
            break;
        }
    }
}
