#include <avr/io.h>
#define F_CPU 8000000
#include <util/delay.h>
#include "classTimer.h"

void Timers::PartirCompteur(){

    //switch (leType) {
    //case TIMER0:
    //    TCCR0B |= (1 << CS02) | (1 << CS00); // p.104 prescaler 1/1024 (ou /8)
    //    break;
    //case TIMER1:
    //    TCCR1B |= (1 << CS12) | (1 << CS10);
    //    break;
    //case TIMER2:
    //    TCCR2B |= (1 << CS22) | (1 << CS20);
    //    break;
    //}
    switch (leType) {
    case TIMER0:
        TCCR0B |= prescaler_; //partir compteur en activant le prescaler (ChoisirPrescaler)
        break;
    case TIMER1:
        TCCR1B |= prescaler_;
        break;
    case TIMER2:
        TCCR2B |= prescaler_;
        break;
    }
}


void Timers::ArretCompteur() {

    switch (leType) {
    case TIMER0:
        TCCR0B &= ~((1 << CS02) | (1 << CS01) | (1 << CS00)); //tous bits a 0 = desactive prescaler
        break;
    case TIMER1:
        TCCR1B &= ~((1 << CS12) | (1 << CS11) | (1 << CS10));
        break;
    case TIMER2:
        TCCR2B &= ~((1 << CS22) | (1 << CS21) | (1 << CS20));
        break;
    }
}


void Timers::DutyCylcle(int pourcentage){

    //jsp si c necessaire:
    //if (pourcentage < 0) pourcentage = 0; //empeche negatif
    //if (pourcentage > 100) pourcentage = 100; //empeche plus de 100% (debordement d e255)

    uint8t valeurOCR = (pourcentage / 100.0) * 255; 

    switch (leType) {
    case TIMER0:
        OCR0A = valeurOCR; // OCRxA -> durée du signal haut (duty cycle)
        break;
    case TIMER1:
        OCR1A = valeurOCR;
        break;
    case TIMER2:
        OCR2A = valeurOCR;
        break;
    }

}


void Timers::ConfigurationCTC() { //mode ctc -> bit WGMx1 = 1 et OCRxA = valeurCtc

    switch (leType) {
    case TIMER0:
        TCCR0A |= (1 << WGM01);
        OCR0A = valeurCtc;
        break;
    case TIMER1: // 16 bits
        TCCR1B |= (1 << WGM12);
        OCR1A = valeurCtc;
        break;
    case TIMER2:
        TCCR2A |= (1 << WGM21);
        OCR2A = valeurCtc;
        break;
    }
}
