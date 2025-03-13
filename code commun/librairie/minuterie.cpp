#include <avr/io.h>
#define F_CPU 8000000
#include <util/delay.h>
#include "minuterie.h"


Minuterie::Minuterie(TypeMinuterie type, ModeMinuterie mode, uint16_t valeurCtc, uint16_t prescaler)
    : leType_(type), leMode_(mode), valeurCtc_(valeurCtc)
{
    prescaler_ = choisirPrescaler(prescaler);
    if (leType_ == MINUTERIE1)
    {
        leMode_ = CTC; // MINUTERIE1 doit être en mode CTC pour calculer le delais
    }
    else if (leType_ == MINUTERIE0 || leType_ == MINUTERIE2)
    {
        leMode_ = PWM; // MINUTERIE0 et MINUTERIE2 doivent être en mode PWM vu qu'on ne peut pas utiliser ;eMINUTERIE1
    }
    if (mode == CTC)
    {
        configurationCTC();
    }
    else if (mode == PWM)
    {
        configurationPWM();
    } // else if(mode == NORMAL){
    //     configurationNormal();
    // }
}

TypeMinuterie Minuterie::accederType(){
        return leType_;
}

uint16_t Minuterie::choisirPrescaler(uint16_t valeur)
{ // page 131
    switch (leType_)
    {

        case MINUTERIE0:
            if (valeur == 1)
                return (1 << CS00);
            if (valeur == 8)
                return (1 << CS01);
            if (valeur == 64)
                return (1 << CS00) | (1 << CS01);
            if (valeur == 256)
                return (1 << CS02);
            if (valeur == 1024)
                return (1 << CS00) | (1 << CS02);

            break;

        case MINUTERIE1:

            break;

        case MINUTERIE2:
            if (valeur == 1)
                return (1 << CS20);
            if (valeur == 8)
                return (1 << CS21);
            if (valeur == 64)
                return (1 << CS20) | (1 << CS21);
            if (valeur == 256)
                return (1 << CS22);
            if (valeur == 1024)
                return (1 << CS20) | (1 << CS22);

            break;
    }
    return 0;
}

void Minuterie::configurationPWM()
{ // 130
    switch (leType_)
    {
        case MINUTERIE0:
            TCCR0A = (1 << COM0A1) | (1 << COM0B1) | (1 << WGM00);
            TCCR0B = (1 << CS01);

            break;

        case MINUTERIE1:

            break;

        case MINUTERIE2:

            TCCR2A = (1 << COM2A1) | (1 << COM2B1) | (1 << WGM20);
            TCCR2B = (1 << CS21);

            break;
    }
}
void Minuterie::ajustementPwm(uint8_t dureeA, uint8_t dureeB)
{

    rapportCycle(dureeA, dureeB);
    configurationPWM();
}

void Minuterie::partirCompteur()
{

    switch (leType_)
    {
        case MINUTERIE0:
            TCCR0B |= prescaler_; // partir compteur en activant le prescaler (ChoisirPrescaler)
            break;

        case MINUTERIE1:
            TCNT1 = 0;
            TCCR1B |= prescaler_;
            break;

        case MINUTERIE2:
            TCCR2B |= prescaler_;
            break;
    }
}

void Minuterie::arretCompteur()
{

    switch (leType_)
    {
        case MINUTERIE0:
            TCCR0B &= ~((1 << CS02) | (1 << CS01) | (1 << CS00)); // tous bits a 0 = desactive prescaler
            TIMSK0 = 0;
            break;

        case MINUTERIE1:
            TCCR1B &= ~((1 << CS12) | (1 << CS11) | (1 << CS10));
            TIMSK1 = 0;
            break;

        case MINUTERIE2:
            TCCR2B &= ~((1 << CS22) | (1 << CS21) | (1 << CS20));
            TIMSK2 = 0;
            break;
    }
}

void Minuterie::configurationCTC()
{ // mode ctc -> bit WGMx1 = 1 et OCRxA = valeurCtc

    switch (leType_)
    {
        case MINUTERIE0:
            TCNT0 = 0;
            TCCR0A = 0; // reinitialisation
            TCCR0A |= (1 << WGM01);
            OCR0A = valeurCtc_;
            break;
        case MINUTERIE1: // 16 bits
            TCNT0 = 0;
            TCCR1B = 0;
            TCCR1B |= (1 << WGM12);
            OCR1A = valeurCtc_;
            break;
        case MINUTERIE2:
            TCNT2 = 0;
            TCCR2A = 0;
            TCCR2A |= (1 << WGM21);
            OCR2A = valeurCtc_;
            break;
    }
}

void Minuterie::rapportCycle(uint16_t dureeA, uint16_t dureeB)
{

    switch (leType_)
    {
        case MINUTERIE0:
            OCR0A = dureeA; // duty cycle pwm
            OCR0B = dureeB;
            break;

        case MINUTERIE1:
            OCR1A = dureeA;
            break;

        case MINUTERIE2:
            OCR2A = dureeA; // duty cycle pwm
            OCR2B = dureeB;
            break;
    }
}
uint16_t Minuterie::calculPourcentage(uint16_t pourcentage, uint16_t top)
{
    return (pourcentage * top) / 100;
}