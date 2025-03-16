/*###############   Auteurs  #####################
########   TP7 et TP8 classe du Bouton    ########
#####                                        #####
#####        Produit et ecrit par:           #####
0#####           Equipe 5556                 #####
#####        Alexa Kassar (2350528)          #####
#####        Jonathan Volcy (2383299)        #####
#####       Rym Fortas (2385101)             #####
#####        Marily  Lemire (2350146)        #####
#####           INF1900 (groupe 03)          #####
#####                2025                    #####
##################################################


############## Description #####################
Fichier h: Déclaration de la classe "Minuterie" et de ses méethodes 
pour la configuration et l'utilisation des minutries */ 

#include <avr/io.h>

#ifndef MINUTERIE_H
#define MINUTERIE_H

enum TypeMinuterie{MINUTERIE0, MINUTERIE1, MINUTERIE2};
enum ModeMinuterie{CTC, PWM};

class Minuterie
{
public:

    Minuterie(TypeMinuterie type, ModeMinuterie mode, uint16_t valeurCtc=0, uint16_t prescaler =0);

    void partirCompteur();
    void arreterCompteur();
    uint16_t choisirPrescaler(uint16_t ); 
    void comparerSortiesRegistres(uint16_t ,uint16_t ); 
    void ajusterPwm( uint8_t  , uint8_t );
    uint16_t convertirPourcentage(uint16_t  , uint16_t );
    TypeMinuterie accederType();

private:
    TypeMinuterie leType_;
    ModeMinuterie leMode_;
    uint16_t valeurCtc_;
    uint16_t prescaler_;

    void configurerPwm(); 
    void configurerCtc();
  
};

#endif