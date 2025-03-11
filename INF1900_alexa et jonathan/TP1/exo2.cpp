#include <avr/io.h>
#define F_CPU 8000000
#include <util/delay.h>

int main() {
    DDRA = (1 << PA0) | (1 << PA1);

    while (true) {
        PORTA = (1 << PA0);
        _delay_ms(500);
        PORTA = (1 << PA1);
        _delay_ms(500);
    }
}