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
Fichier h: Déclaration de la classe "transmissionUart" 
et des méthodes utilisées pour la communication RS232 */

#ifndef TRANSMISSIONUART_H
#define TRANSMISSIONUART_H
#define F_CPU 8000000

#include <avr/io.h>
#include <util/delay.h>


class TransmissionUart 
{
public:
    TransmissionUart();
    void transmettreChar(char );
    void transmettreString( char* );
    void transmettreEntier(uint16_t );
    
};

#endif