#include <avr/io.h>

#ifndef MINUTERIE_H
#define MINUTERIE_H

enum TypeMinuterie{MINUTERIE0, MINUTERIE1, MINUTERIE2};
enum ModeMinuterie{NORMAL,CTC, PWM};
class Minuterie{
    public:

    Minuterie(TypeMinuterie type, ModeMinuterie mode, uint16_t valeurCtc=0, uint16_t prescaler =0);

    void partirCompteur();
    void arretCompteur();
    uint16_t choisirPrescaler(uint16_t ); // valeur c'est 1024 ou 64 ou8 ou... et la méthode te donne ;es registres à utiliser 
    void rapportCycle(uint16_t ,uint16_t ); // pour le PWM, ici on return les registres dependamment du timer
    void ajustementPwm( uint8_t  , uint8_t );
    uint16_t calculPourcentage(uint16_t  , uint16_t );
    TypeMinuterie accederType();

    private:
    ///uint16t valeurNormal; on fini et on rajoute le normal ok!
    TypeMinuterie leType_;
    ModeMinuterie leMode_;
    uint16_t valeurCtc_; //valeur de compara
    uint16_t prescaler_;


    void configurationPWM(); //pas accesible 
    void configurationCTC();
    //void ConfigurationNormal(); //pas sure de l'utiliser encore 

};
#endif