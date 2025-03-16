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
Fichier h: Déclaration de la classe "Minuterie2" et de ses méethodes 
pour la configuration et l'utilisation des minutries */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include "enum.h"

#ifndef MINUTERIE2_H
#define MINUTERIE2_H


enum class ModeMinuterie2 {CTC, PWM};

class Minuterie2
{
public:
    

    Minuterie2(ModeMinuterie2 mode, uint16_t valeurCtc=0, uint16_t prescaler =0);

    void partirCompteur();
    void arreterCompteur();
    uint16_t choisirPrescaler(uint16_t ); 
    void comparerSortiesRegistres(uint16_t ,uint16_t ); 
    void ajusterPwm( uint8_t  , uint8_t );
    void activerInterruption();
    
   
private:
    
    ModeMinuterie2 leMode_;
    uint16_t valeurCtc_;
    uint16_t prescaler_;
    void configurerPwm(); 
    void configurerCtc();
  
};

#endif