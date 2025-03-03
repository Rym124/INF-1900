//initilisation 

DDRA = (1 << PA);
DDRD &= ~(1<<PD2); // PD2 comme entree) | (1 << PA1);
PORTA = (1 << PA0);

//led colores

void turnLedOff() {
    PORTA &= ~((1 << PA1) | (1 << PA0));
}

void turnRedLed(){
    PORTA |= (1 << PA0);
    PORTA &= ~(1 << PA1);
}

void turnGreenLedOn(){
    PORTA |= (1 << PA1); 
    PORTA &= ~(1 << PA0); 
}

void turnAmberLedOn() {
    turnGreenLedOn();
    _delay_ms(5);
    turnRedLedOn();
    _delay_ms(5);

}