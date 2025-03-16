#include <avr/io.h>
#include <util/delay.h>
#include "classUART.h"
#include "memoire_24.h"
#include "del.h"
#include "bouton.h"
#include "minuterie0.h"
// #include "minuterie1.h"
#include "minuterie2.h"
#include "roues.h"
#include "debug.h"

volatile bool gMinuterieExpiree = false;
volatile bool gBoutonAppuye = false;

ISR(TIMER2_COMPA_vect){
    gMinuterieExpiree = true;
}

ISR(INT0_vect) {
    gBoutonAppuye = true;
}

int main() {
    Del del;
    Minuterie2 timer2(ModeMinuterie2::PWM, 0, 8);
    Roues roue (timer2,0,0);
    // timer2.activerInterruption();
    // timer2.partirCompteur();
    // do {} while(!gMinuterieExpiree);
    // del.allumerVert();
    roue.avancer(timer2, 127,127);

    // Del del;
    // Bouton bountonD2(INT0);
    // do {} while(!gBoutonAppuye);
    // del.allumerRouge();


}