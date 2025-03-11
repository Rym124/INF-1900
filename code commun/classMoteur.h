#ifndef CLASS_MOTEUR
#define CLASS_MOTEUR

#include "classTimer.h"

// enum T{TIMER0, TIMER2};


class Moteurs{
    public:

    Moteurs( Timers letimer, uint16_t vitesseD,uint16_t vitesseG);

    void avancer(Timers , uint16_t, uint16_t);
    void reculer(Timers , uint16_t, uint16_t);

    void tournerDroite(Timers , uint16_t);
    void tournerGauche(Timers, uint16t);
    void arretRoue(Timers);
    void portAvance();
    void portRecule();
    void configuration();
    private:
    Timers timer;
    uint16t vitesseD;
    uint16t vitesseG;

};


#endif