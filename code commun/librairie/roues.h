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
Fichier h: Déclaration de la classe "Roues" et des méthodes 
pour la configuration et l'utilisation des minutries */ 
 
#ifndef CLASSE_ROUES
#define CLASSE_ROUES

#include "minuterie2.h"

class Roues
{
public:

    Roues( Minuterie2 letimer);

    void avancer( uint16_t, uint16_t);
    void reculer(uint16_t, uint16_t);
    void tournerDroite(uint16_t);
    void tournerGauche(uint16_t);
    void arreter();
    void avancerPorts();
    void reculerPorts();
    

private:

    Minuterie2 minuterie_;
    
};


#endif
