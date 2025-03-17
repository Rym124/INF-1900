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
Fichier h: Déclaration de la classe "Minuterie1" et de ses méthodes 
pour la configuration et l'utilisation des minutries */ 

#include <avr/io.h>
#include <avr/interrupt.h>

#ifndef MINUTERIE1_H
#define MINUTERIE1_H


class Minuterie1
{
public:

    Minuterie1(uint16_t valeurCtc=0, uint16_t prescaler =0);
    void partirCompteur();
    void arreterCompteur();
    uint16_t choisirPrescaler(uint16_t ); 
    void comparerSortiesRegistres(uint16_t ); 
    void activerInterruption();
    uint16_t convertirPourcentage(uint16_t pourcentage, uint16_t valeurMax);
   
private:
    uint16_t valeurCtc_;
    uint16_t prescaler_;
    void configurerCtc();
  
};

#endif
