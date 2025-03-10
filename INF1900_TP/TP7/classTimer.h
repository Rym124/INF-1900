#include <avr/io.h>

#ifndef CLASSTIMER_H
#define CLASSTIMER_H

class Timers{

    public:

    enum TypeTimer{TIMER1, TIMER0, TIMER2};
    enum ModeTimer{NORMAL,CTC, PWM};

    Timers(TypeTimer type, ModeTimer mode, uint16_t valeurCtc=0, uint16_t prescaler =0){};

    void PartirCompteur();
    void ArretCompteur();

    void ChoisirPrescaler(int valeur); // valeur c'est 1024 ou 64 ou8 ou... et la méthode te donne ;es registres à utiliser 
    
    void DutyCylcle(int pourcentage ); // pour le PWM, ici on return les registres dependamment du timer

    private:
    uint16_t valeurCtc_;
    ///uint16_t valeurNormal_; on fini et on rajoute le normal ok!
    TypeTimer leType;
    ModeTimer leMode;
    
    void ConfigurationPWM(); //pas accesible 
    void ConfigurationCTC();
    //void ConfigurationNormal(); pas sure de l'utiliser encode 

}
#endif