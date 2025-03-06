#include <avr/io.h>
#define F_CPU 8000000
#include <util/delay.h>
#include "classTimer.h"



Timers::Timers(TypeTimer type, ModeTimer mode, uint16_t valeurCtc, uint16_t prescaler)
    : leType_(type), leMode_(mode), valeurCtc_(valeuCtc) {
    prescaler_= gChoisirPrescaler(prescaler);
    if (leType_ == TIMER1) {
        leMode_ = CTC;  // TIMER1 doit être en mode CTC pour calculer le delais
    } else if (leType_ == TIMER0 || leType_ == TIMER2) {
        leMode_ = PWM;  // TIMER0 et TIMER2 doivent être en mode PWM vu qu'on ne peut pas utiliser ;etimer1
    }
    if (mode == CTC) {
        configurationCTC();
    } else if (mode == PWM) {
        configurationPWM();
    } //else if(mode == NORMAL){
    //     configurationNormal();
    // }
} 

uint16_t Timers:: ChoisirPrescaler(uint16_t valeur){ //page 131 
    switch (leType_)
    {
    // case TIMER1:
    //     if (valeur == 1){return (1<<CS10)};
    //     if(valeur == 8){return (1<<CS11)};
    //     if(valeur == 64){return (1<<CS10)|(1<<CS11)}
    //     if (valeur == 256){return (1<<CS12)}
    //     if (valeur ==1024){return (1<<CS10)|(1<<CS12)}
    //     break;
    
    case TIMER0:
        if (valeur == 1){return (1<<CS00)};
        if(valeur == 8){return (1<<CS01)};
        if(valeur == 64){return (1<<CS00)|(1<<CS01)}
        if (valeur == 256){return (1<<CS02)}
        if (valeur ==1024){return (1<<CS00)|(1<<CS02)}
     
       break;
    
    case TIMER2:
        if (valeur == 1){return (1<<CS20)};
        if(valeur == 8){return (1<<CS21)};
        if(valeur == 64){return (1<<CS20)|(1<<CS21)}
        if (valeur == 256){return (1<<CS22)}
        if (valeur == 1024){return (1<<CS20)|(1<<CS22)}
    
        break;

    }
    return 0;
}

void Timers::configurationPWM(){ //130
    switch (leType_){
        case TIMER0:
        TCCR0A = (1 << COM0A1) | (1 << COM0B1) | (1 << WGM00);
        TCCR0B = (1 << CS01);    
        //TCCR0C = 0;
        break;
        case TIMER2:

        TCCR2A = (1 << COM2A1) | (1 << COM2B1) | (1 << WGM20);
        TCCR2B = (1 << CS21);
        //TCCR0C = 0;
        break;
    }
}
void Timers::ajustementPwm( uint8_t dureeA , uint8_t dureeB) {

    OCR1A = (dureeA / 100.0) * 255; // gauche
    OCR1B = (dureeB / 100.0) * 255; // droite
    // on peut mettre le dutycycle ici 

    configurationPWM();
}





