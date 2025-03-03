#include <avr/io.h>
#define F_CPU 8000000
#include <util/delay.h>

bool debounceD2() {
if (PIND & (1 << PD2)) {
	_delay_ms(10);
	return PIND & (1 << PD2);
}
else {
	return false;
}
}

int main() {

DDRA = (1 << PA);
DDRD &= ~(1<<PD2); // PD2 comme entree) | (1 << PA1);
PORTA = (1 << PA0);

while(true){

	if (debounceD2()) {
		while (debounceD2()) {
			PORTA = 0;
		}
}
	else {
		PORTA =(1 << PA0);
		_delay_ms(500);
		PORTA = (1 << PA1);
		_delay_ms(50);
		
	}
}
}
