
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
Fichier cpp: méthodes de deboggage*/

#include "classUART.h"
#include "debug.h"

void printf(uint16_t valeur) 
{
    static TransmissionUart uart;
    uart.transmettreEntier(valeur);
}

void printf( char* message) 
{
    static TransmissionUart uart;
    uart.transmettreString(message);
}