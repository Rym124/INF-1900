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


############## Broches(I/O) ####################
INPUT: D2 connected to the push button 
OUTPUT: PIN A1 et PIN A0 
PIN A0 is connected to the positive(+) post
PIN A1 is connected to the negative(-) post


############## Description #####################
Fichier pour tester quelques méthodes 
de notre librairie*/ 

#define DELAI5 5
#define DELAI30 30
#define DELAI4000 4000
#define DELAI2000 2000
#define VALEUR_DEBUG 2
#define LONGUEUR 29
#define PRESCALER 8
#define VITESSE 127
#define POUCENTAGE50 50
#define POURCENTAGE75 75
#define VALEUR_MAX 255
#define F_CPU 8000000

#include <avr/io.h>
#include <util/delay.h>
#include "classUART.h"
#include "memoire_24.h"
#include "del.h"
#include "bouton.h"
#include "minuterie.h"
#include "roues.h"
#include "debug.h"


#ifdef DEBUG
# define DEBUG_PRINT(x) printf (x) 
#else
# define DEBUG_PRINT(x) do {} while (0) 
#endif

volatile bool gBoutonAppuye = false;

ISR(INT0_vect) 
{
    _delay_ms(DELAI30);
    if(PIND & (1 << PD2))
        gBoutonAppuye = true;
    else
        gBoutonAppuye = false;
    
    EIFR |= (1 << INTF1);
    
}

int main()
{

    _delay_ms(DELAI5);
   DEBUG_PRINT(VALEUR_DEBUG);
   _delay_ms(DELAI5);

    TransmissionUart uart;
    Minuterie laMinuterie (MINUTERIE0, PWM,0,PRESCALER);
    Roues leMoteur(laMinuterie,0,0);
    Del del;
    Bouton boutonD2(INT0);
    Memoire24CXXX memoire;

    char* chaine = "BIENVENUE CHERS CORRECTEURS!";
    uint16_t adresse = 0x00;

    memoire.ecriture(adresse, chaine, LONGUEUR);
    char donneeLu[LONGUEUR];
    memoire.lecture(adresse, donneeLu, LONGUEUR );
    uart.transmettreString(donneeLu);

    leMoteur.avancer(laMinuterie,VITESSE,VITESSE);
    _delay_ms(DELAI4000);

    leMoteur.reculer(laMinuterie, laMinuterie.convertirPourcentage(POURCENTAGE75,VALEUR_MAX), laMinuterie.convertirPourcentage(85,255));
    _delay_ms(DELAI2000);

    leMoteur.arreter(laMinuterie);
    _delay_ms(DELAI2000);

    leMoteur.tournerDroite(laMinuterie,laMinuterie.convertirPourcentage(POUCENTAGE50,VALEUR_MAX));
    _delay_ms(DELAI2000);

    leMoteur.arreter(laMinuterie);
    _delay_ms(DELAI4000);

    leMoteur.tournerGauche(laMinuterie, laMinuterie.convertirPourcentage(POUCENTAGE50 ,VALEUR_MAX));
    _delay_ms(DELAI4000);

    leMoteur.arreter(laMinuterie);

    while (true) 
    {
        del.allumerRouge();
        do {} while(!gBoutonAppuye);
        do {del.allumerAmbre();} while (gBoutonAppuye);
        del.allumerVert();
        do {} while(!gBoutonAppuye);
        del.allumerRouge();
        do {} while(gBoutonAppuye);
        del.eteindre();
        do {} while (!gBoutonAppuye);
        del.allumerVert();
        do {} while (gBoutonAppuye);
        del.allumerRouge();
    }
 }
