#include <avr/io.h>
#define F_CPU 8000000UL
#include <util/delay.h>
#include "memoire_24.h"



void turnRedLedOn() {
   PORTA |= (1 << PA0);  
   PORTA &= ~(1 << PA1); 
}

void turnGreenLedOn() {
   PORTA |= (1 << PA1);  
   PORTA &= ~(1 << PA0); 
}


int main(){
   DDRA |= (1 << PA0) | (1 << PA1); 

   const char* chaine = "*P*O*L*Y*T*E*C*H*N*I*Q*U*E* *M*O*N*T*R*E*A*L*";
   Memoire24CXXX memoire;
 
   uint8_t longueur = 0;
   while (chaine[longueur] != '\0') {
        longueur++;
    }

   char tableau[longueur];
    
   const uint16_t adresse = 0x0000;

   for (int i = 0; i <= longueur; i++){
      const uint8_t donnee = (i < longueur) ? chaine[i] : 0x00;
      memoire.ecriture(adresse + i , donnee);
      _delay_ms(5);
   }

   for (int i = 0; i <= longueur; i++){
      uint8_t characterLu;
      memoire.lecture(adresse + i , &characterLu);
      tableau[i] = characterLu;
   }

   for (uint8_t i = 0; i < longueur; i++) {
        if (chaine[i] == tableau[i]) {
            turnGreenLedOn();
        }
        else {
            turnRedLedOn();
        }
    }
}
   