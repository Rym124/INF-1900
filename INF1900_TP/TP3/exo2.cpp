#include <avr/io.h>
#define F_CPU 8000000
#include <util/delay.h>

constexpr uint8_t TIME_UNIT= 1;
constexpr uint8_t REPETITION_UNIT_ONE = 125;
constexpr uint16_t REPETITION_UNIT_TWO= 800;



void delayMS(uint16_t repetition) {
    for (uint16_t i = 0; i < repetition; i++) {
        _delay_ms(TIME_UNIT);
    }
}

void delayUS(uint16_t repetition) {
    for (uint16_t i = 0; i < repetition; i++) {
        _delay_us(TIME_UNIT);
    }
}

void turnWheelOn(){
    PORTD |= (1 << PD1);
}
void turnWheelOff(){
    PORTD &= ~(1 << PD1);
}

int main() {
    DDRD |= (1 << PD0) | (1 << PD1);
     
    
        //frequence de 60HZ
        turnWheelOff();
        delayMS(2000);
        
        for (uint16_t i = 0; i < REPETITION_UNIT_ONE; i++) {
            turnWheelOn();
            delayMS(4);
            turnWheelOff();
            delayMS(12);
        }

        for (uint16_t i = 0; i < REPETITION_UNIT_ONE; i++) {       
            turnWheelOn();
            delayMS(8);
            turnWheelOff();
            delayMS(8);
        }

        for (uint16_t i = 0; i < REPETITION_UNIT_ONE; i++) {
            turnWheelOn();
            delayMS(12);
            turnWheelOff();
            delayMS(4);
        }

        for (uint16_t i = 0; i < REPETITION_UNIT_ONE; i++) {
            turnWheelOn();
            delayMS(16);
        }
        
        // frequence de 400HZ
        turnWheelOff();
        delayMS(2000);
    
        for (uint16_t i = 0; i < REPETITION_UNIT_TWO; i++) {
            turnWheelOn();
            delayUS(625);
            turnWheelOff();
            delayUS(1875);
        }

        for (uint16_t i = 0; i < REPETITION_UNIT_TWO; i++) {
            turnWheelOn();
            delayUS(1250);
            turnWheelOff();
            delayUS(1250);
        }
        
        for (uint16_t i = 0; i < REPETITION_UNIT_TWO; i++) {
            turnWheelOn();
            delayUS(1875);
            turnWheelOff();
            delayUS(625);
        }
        
        for (uint16_t i = 0; i < REPETITION_UNIT_TWO; i++) {
            turnWheelOn();
            delayUS(2500);
        }
        turnWheelOff();
}
