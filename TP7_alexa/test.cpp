#include "del.h"
#include "intExt.h"

volatile bool gBoutonAppuye = false;

ISR(INT0_vect) {
    _delay_ms(30);
    if(PIND & (1 << PD2))
        gBoutonAppuye = true;
    else
        gBoutonAppuye = false;
    
    EIFR |= (1 << INTF1);
    
}

int main() {
    DEL del(PA0, PA1, &DDRA, &PORTA);
    InterruptionExterne boutonD2(INT0, MONTANT);
    while (true) {
        del.allumerRouge();
        do {} while(!gBoutonAppuye);
        boutonD2.attenteFrontDescendant();
        do {del.allumerAmbre();} while (gBoutonAppuye);
        del.allumerVert();
        boutonD2.attenteFront();
        do {} while(!gBoutonAppuye);
        del.allumerRouge();
        do {} while(gBoutonAppuye);
        del.eteindre();
        do {} while (!gBoutonAppuye);
        del.allumerVert();
        do {} while (gBoutonAppuye);
        del.allumerRouge();
    }
}