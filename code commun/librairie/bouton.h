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
Fichier h: Délaration de la classe "Bouton" et 
des méthodes qui permettent d'utiliser un bouton par 
scrutation ou par interruption*/


#define F_CPU 8000000
#define AUCUNE_INTERRUPTION 3
#define DELAI_ANTI_REBOND 10

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

enum ModeDeclenchement {MONTANT, DESCENDANT, FRONT, BAS};
enum class Port {A, B, C, D};

class Bouton {
public:

    Bouton(uint8_t interruption, ModeDeclenchement mode);
    Bouton(uint8_t interruption);
    Bouton(Port port, uint8_t pin);
    void activerInterruption(ModeDeclenchement mode);
    void desactiverInterruption();
    bool estAppuye();


private:

    void attendreFrontMontant();
    void attendreFrontDescendant();
    void attendreFront();
    void attendreBas();

    uint8_t interruption_;
    bool utiliseInterruption_;
    Port port_;
    uint8_t pin_;
    

};