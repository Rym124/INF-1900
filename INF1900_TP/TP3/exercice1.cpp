#include <avr/io.h>
#define F_CPU 8000000
#include <util/delay.h>

constexpr uint8_t DELAY_100_US = 100;
 void delay100US(uint8_t repetition){
    for(int i=0; i < repetition; i++){
        _delay_us(DELAY_100_US);
    }
} 
enum State {
    HUNDRED,
    FIFTY,
    TWENTYFIVE,
    OFF
};

State currentState = HUNDRED;

int main() {
    DDRA |= (1 << PA0) | (1 << PA1);

    while (true) {
        switch(currentState){
            case HUNDRED:
            PORTA |= (1 << PA0);
            PORTA &= ~(1 << PA1);
            delay100US(10000);
            currentState = FIFTY;
            break;

            case FIFTY:
            for (int i=0; i < 500; i++ ){
            PORTA |= (1 << PA0);
            PORTA &= ~(1 << PA1);
            delay100US(20);
            PORTA &= ~(1 << PA0);}
            currentState= TWENTYFIVE;
            break;

            case TWENTYFIVE:
            for (int i=0; i < 500; i++ ){
            PORTA |= (1 << PA0);
            PORTA &= ~(1 << PA1);
            delay100US(40);
            PORTA &= ~(1 << PA0);
            }
            currentState = OFF;
            break;
            
            case OFF:
            PORTA &= ~(1<< PA0);
            break;
        }
    }  
}