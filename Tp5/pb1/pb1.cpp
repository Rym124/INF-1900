#include <avr/io.h>
# define F_CPU 8000000UL
#include <util/delay.h>
#include <avr/interrupt.h>


#include"memoire_24.h"
// Rym Fortas et Marily Lemire
using namespace std;

void initialisation(){

    DDRB |= (1<<PB0);
    DDRB |= (1<<PB1);
    
}

void allumeVert()
{
    PORTB &= ~(1 << PB0);
    PORTB |= (1 << PB1);
}
void allumeRouge()
{
    PORTB |= (1 << PB0);
    PORTB &= ~(1 << PB1);
}



int main(){
    bool verifier = false;
    
    initialisation();

    Memoire24CXXX memoire = Memoire24CXXX();
    const uint16_t adresse = 0x0000;
    char texte[] = "*P*O*L*Y*T*E*C*H*N*I*Q*U*E* *M*O*N*T*R*E*A*L*EE";  
    int longueur = sizeof(texte);
    char aLire [longueur];

    memoire.ecriture(adresse, (uint8_t*) texte, longueur);  
    _delay_ms(5); 
    memoire.lecture(adresse, (uint8_t*) aLire, longueur) ;
    
    char text[] = "*P*O*L*Y*T*E*C*H*N*I*Q*U*E* *M*O*N*T*R*E*A*L*LL";
    for(uint8_t i =0; i<longueur; i++){

        if (text[i] != aLire[i]) {
            verifier = false; 
            break;
        }
    }
    if(verifier) allumeVert();
    else allumeRouge();
    
}
