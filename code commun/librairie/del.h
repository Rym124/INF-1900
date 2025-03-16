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
Fichier h: Déclaration de la classe "Del" et des méthodes
pour l'utilisation et le fonctionnement de la Del*/

#define F_CPU 8000000

#include <avr/io.h>
#include <util/delay.h>

class Del 
{
public:
    
    Del(uint8_t bornePositive, uint8_t borneNegative, volatile uint8_t* ddr, volatile uint8_t* port);
    Del();

    void allumerRouge();
    void allumerVert();
    void allumerAmbre();
    void eteindre();
    void clignoterVert(uint16_t dureeMs);
    void clignoterRouge(uint16_t dureeMs);
    void clignoterVert(uint8_t nombreFois, uint16_t frequence);
    void clignoterRouge(uint8_t nombreFois, uint16_t frequence);

private:
    uint8_t bornePositive_, borneNegative_;
    volatile uint8_t* port_, * ddr_;

    const static uint8_t DELAI_AMBRE_MS = 5;
    const static uint8_t FREQUENCE_CLIGNOTEMENT_HZ = 1;
};