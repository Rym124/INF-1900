#include <avr/io.h>
#define F_CPU 8000000
#include <util/delay.h>
#include "classUART.h"
#include "memoire_24.h"
#include "del.h"
#include "bouton.h"
#include "minuterie.h"
#include "roues.h"
#include "debug.h"

#ifdef DEBUG
# define DEBUG_PRINT(x) printf (x) // ou par RS-232
#else
# define DEBUG_PRINT(x) do {} while (0) // code mort
#endif

volatile bool gBoutonAppuye = false;

ISR(INT0_vect) {
    _delay_ms(30);
    if(PIND & (1 << PD2))
        gBoutonAppuye = true;
    else
        gBoutonAppuye = false;
    
    EIFR |= (1 << INTF1);
    
}

int main()
{


    _delay_ms(5);
   DEBUG_PRINT(2);
   _delay_ms(5);
   
   //essaie classe uart et memoire
    UART uart;
    
    char* chaine = "AQR";
    Memoire24CXXX memoire;
     
    uint16_t adresse = 0x00;
    memoire.ecriture(adresse, chaine, 4);
    char donneeLu[4];
    memoire.lecture(adresse, donneeLu, 4 );
    uart.transmissionParBit(donneeLu);



    //essaie classe moteur et Minuterie
    Minuterie laMinuterie (MINUTERIE0, PWM,0,8);
    Roues leMoteur(laMinuterie,0,0);

    leMoteur.avancer(laMinuterie,127,127);
    _delay_ms(4000);
    leMoteur.reculer(laMinuterie, laMinuterie.calculPourcentage(75,255), laMinuterie.calculPourcentage(85,255));
    _delay_ms(2000);
    leMoteur.arretRoue(laMinuterie);
    _delay_ms(2000);
    leMoteur.tournerDroite(laMinuterie,laMinuterie.calculPourcentage(50,255));
    _delay_ms(2000);
    leMoteur.arretRoue(laMinuterie);
    _delay_ms(4000);
    leMoteur.tournerGauche(laMinuterie, laMinuterie.calculPourcentage(50 ,255));
    _delay_ms(4000);
    leMoteur.arretRoue(laMinuterie);

    //essaie del 
    DEL del;
    Bouton boutonD2(INT0);
    while (true) {
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
