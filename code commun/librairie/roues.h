#ifndef CLASSE_ROUES
#define CLASSE_ROUES

#include "minuterie.h"

// enum T{TIMER0, TIMER2};


class Roues{
    public:

    Roues( Minuterie letimer, uint16_t vitesseD,uint16_t vitesseG);

    void avancer(Minuterie , uint16_t, uint16_t);
    void reculer(Minuterie , uint16_t, uint16_t);

    void tournerDroite(Minuterie , uint16_t);
    void tournerGauche(Minuterie, uint16_t);
    void arretRoue(Minuterie);
    void portAvance();
    void portRecule();
    void configuration();
    private:
    Minuterie minuterie_;
    uint16_t vitesseDroite_;
    uint16_t vitesseGauche_;

};


#endif