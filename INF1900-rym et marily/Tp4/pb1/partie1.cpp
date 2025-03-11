#include <avr/io.h>
#define F_CPU 8000000
#include <util/delay.h>
#include <avr/interrupt.h>

// Rym Fortas et Marily Lemire

// Tableau 2:
/*
Entrées: A0 et A1
Sortie: D2
+--------------+------------+------------+----------------+
| État présent | Entrée (A) | État futur | Sortie(Z)      |
+--------------+------------+------------+----------------+
| ROUGE        | 0          | ROUGE      | couleur rouge  |
| ROUGE        | 1          | AMBRE      | couleur ambre  |
| AMBRE        | 0          | VERT       | couleur verte  |
| AMBRE        | 1          | AMBRE      | couleur ambre  |
| VERT         | 0          | VERT       | couleur verte  |
| VERT         | 1          | ROUGE2     | couleur rouge  |
| ROUGE2       | 0          | OFF        | aucune couleur |
| ROUGE2       | 1          | ROUGE2     | couleur rouge  |
| OFF          | 0          | OFF        | aucune couleur |
| OFF          | 1          | VERT2      | couleur verte  |
| VERT2        | 0          | ROUGE      | coueur rouge   |
| VERT2        | 1          | VERT2      | couleur verte  |
+--------------+------------+------------+----------------+
*/

enum class colourState
{
    ROUGE,
    ROUGE2,
    AMBRE,
    VERT,
    VERT2,
    OFF,
};


//uint8_t boutton = 0 ;
volatile bool ispressed = false;

volatile colourState etat_present = colourState::ROUGE;
ISR ( INT0_vect ) {

// laisser un délai avant de confirmer la réponse du

// bouton-poussoir: environ 30 ms (anti-rebond)

_delay_ms ( 30 );

if (PIND & (1 << PD2)) {
    ispressed = true;
}
else ispressed = false;


//boutton = 1;
// se souvenir ici si le bouton est pressé ou relâché

//modifier

// changements d'état tels que ceux de la

// semaine précédente

//modifier

// Voir la note plus bas pour comprendre cette instruction et son rôle

EIFR |= (1 << INTF0) ;

}

void initialisation ( void ) {

// cli est une routine qui bloque toutes les interruptions.

// Il serait bien mauvais d'être interrompu alors que

// le microcontrôleur n'est pas prêt...

cli ();



// configurer et choisir les ports pour les entrées

// et les sorties. DDRx... Initialisez bien vos variables

DDRA |= (1 << PA0);
DDRA |= (1 << PA1);
DDRD &= ~(1 << PD2);


// cette procédure ajuste le registre EIMSK

// de l’ATmega324PA pour permettre les interruptions externes

EIMSK |= (1 << INT0) ;
//Le registre EIMSK (External Interrupt Mask Register) permet de configurer quels interrupt externes sont activés. 
//Ici, (1 << INT0) active l'interruption externe INT0, ce qui signifie que lorsque l'interruption INT0 est déclenchée, 
//elle sera prise en compte par le microcontrôleur. 
//|= est un opérateur qui permet d'ajouter le bit à 1 pour activer INT0 tout en conservant les autres bits du registre inchangés.



// il faut sensibiliser les interruptions externes aux

// changements de niveau du bouton-poussoir

// en ajustant le registre EICRA

EICRA |= ( 1<< ISC00) ; // front montant et descendant



// sei permet de recevoir à nouveau des interruptions.

sei ();

}

void allumeRouge()
{

    PORTA |= (1 << PA0);
    PORTA &= ~(1 << PA1);
}

void allumeAmbre()
{

    while (ispressed){
        PORTA |= (1 << PA0);
        PORTA &= ~(1 << PA1);
        _delay_ms(5);
        PORTA |= (1 << PA1);
        PORTA &= ~(1 << PA0);
        _delay_ms(8);
    }
        
    
}

void allumeVert()
{
    while (!ispressed){
    PORTA &= ~(1 << PA0);
    PORTA |= (1 << PA1);}
}

void allumeRouge2()
{

     while (ispressed){
        PORTA |= (1 << PA0);
        PORTA &= ~(1 << PA1);}
        
    
}
void eteinte()
{
    while (!ispressed){
    PORTA &= ~(1 << PA0);
    PORTA &= ~(1 << PA1);}
}


void allumeVert2()
{
    while (ispressed){
    PORTA &= ~(1 << PA0);
    PORTA |= (1 << PA1);
    }     
   
}



int main()
{
    initialisation();
    

    

    while (true)
    {
        switch (etat_present)
        {
        case colourState::ROUGE:
            allumeRouge();
            if(ispressed)
            etat_present = colourState::AMBRE;
            break;

        case colourState::AMBRE:
            allumeAmbre();
            etat_present = colourState::VERT;
            
            break;

        case colourState::VERT:
            allumeVert();
            
                etat_present = colourState::ROUGE2;
            
            break;

        case colourState::ROUGE2:
            allumeRouge2();
            etat_present = colourState::OFF;
            break;

        case colourState::OFF:
            eteinte();
            etat_present = colourState::VERT2;
            
            break;

        case colourState::VERT2:
            allumeVert2();
            etat_present = colourState::ROUGE;

            break;
        }
    }
}
