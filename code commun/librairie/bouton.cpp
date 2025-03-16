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
Fichier cpp: Classe "Bouton" qui permet d'utiliser un bouton par 
scrutation ou par interruption*/


#include "bouton.h"

Bouton::Bouton(uint8_t interruption, ModeDeclenchement mode) : interruption_(interruption), utiliseInterruption_(true)
{
    cli();
    switch (interruption)
    {
        case INT0:
            if (mode == MONTANT)
            {
                EICRA |= (1 << ISC01) | (1 << ISC00);
            }
            else if (mode == DESCENDANT)
            {
                EICRA |= (1 << ISC01);
                EICRA &= ~(1 << ISC00);
            }
            else if (mode == FRONT)
            {
                EICRA &= ~ (1 << ISC01);
                EICRA |= (1 << ISC00);
            }
            else if (mode == BAS) 
            {
                EICRA &= ~((1 << ISC00) | (1 << ISC01));
            }

            EIMSK |= (1 << INT0);
            port_ = Port::D;
            pin_ = PD2;
            break;
        
        case INT1:
            if (mode == MONTANT) 
            {
                EICRA |= (1 << ISC11) | (1 << ISC10);
            }

            else if (mode == DESCENDANT) 
            {
                EICRA |= (1 << ISC11);
                EICRA &= ~(1 << ISC10);
            }

            else if (mode == FRONT) 
            {
                EICRA &= ~(1 << ISC11);
                EICRA |= (1 << ISC10);
            }

            else if (mode == BAS) 
            {
                EICRA &= ~((1 << ISC11) | (1 << ISC10));
            }

            EIMSK |= (1 << INT1);
            port_ = Port::D;
            pin_ = PD3;
            break;

        case INT2:
            if (mode == MONTANT) 
            {
                EICRA |= (1 << ISC21) | (1 << ISC20);
            }

            else if (mode == DESCENDANT) 
            {
                EICRA |= (1 << ISC21);
                EICRA &= ~(1 << ISC20);
            }

            else if (mode == FRONT) 
            {
                EICRA &= ~ (1 << ISC21);
                EICRA |= (1 << ISC20);
            }

            else if (mode == BAS) 
            {
                EICRA &= ~((1 << ISC21) | (1 << ISC20));
            }

            EIMSK |= (1 << INT2);
            port_ = Port::B;
            pin_ = PB2;
            break;
        }
    sei();
}

Bouton::Bouton(uint8_t interruption) : Bouton(interruption, FRONT) {}

Bouton::Bouton(Port port, uint8_t pin) : interruption_(AUCUNE_INTERRUPTION), utiliseInterruption_(false), port_(port), pin_(pin) {}

void Bouton::activerInterruption(ModeDeclenchement mode) 
{
    switch (mode)
    {
        case FRONT:
           attendreFront();
            break;

        case MONTANT:
           attendreFrontMontant();
            break;

        case DESCENDANT:
           attendreFrontDescendant();
            break;

        case BAS:
           attendreBas();
            break;
        
        default:
            break;
    }
}

void Bouton::desactiverInterruption() 
{
    if (utiliseInterruption_) 
    {
        EIMSK &= ~(1 << interruption_);
        utiliseInterruption_ = false;
    }
}

bool Bouton::estAppuye() 
{
    _delay_ms(DELAI_ANTI_REBOND);

    if(port_ == Port::A) 
    {
        return (PINA & (1 << pin_));
    }

    else if(port_ == Port::B) 
    {
        return (PINB & (1 << pin_));
    }

    else if(port_ == Port::C) 
    {
        return (PINC & (1 << pin_));
    }

    else if(port_ == Port::D) 
    {
        return (PIND & (1 << pin_));
    }

    return false;
}


void Bouton::attendreFront() 
{
    switch (interruption_)
    {
        case INT0:
            EIMSK &= ~(1 << INT0);
            EICRA &= ~(1 << ISC01);
            EICRA |= (1 << ISC00);
            EIMSK |= (1 << INT0);
            break;

        case INT1:
            EIMSK &= ~(1 << INT1);
            EICRA &= ~(1 << ISC11);
            EICRA |= (1 << ISC10);
            EIMSK |= (1 << INT1);
            break;
        
        case INT2:
            EIMSK &= ~(1 << INT2);
            EICRA &= ~(1 << ISC21);
            EICRA |= (1 << ISC20);
            EIMSK |= (1 << INT2);
            break;
    }
}

void Bouton::attendreFrontMontant() 
{
    switch(interruption_) 
    {

        case INT0:
            EIMSK &= ~(1 << INT0);
            EICRA |= (1 << ISC01) | (1 << ISC00);
            EIMSK |= (1 << INT0);
            break;

        case INT1:
            EIMSK &= ~(1 << INT1);
            EICRA |= (1 << ISC11) | (1 << ISC10);
            EIMSK |= (1 << INT1);
            break;

        case INT2:
            EIMSK &= ~(1 << INT2);
            EICRA |= (1 << ISC21) | (1 << ISC20);
            EIMSK |= (1 << INT2);
            break;
    }
}

void Bouton::attendreFrontDescendant() 
{
    switch (interruption_) 
    {
        case INT0:
            EIMSK &= ~(1 << INT0);
            EICRA |= (1 << ISC01);
            EICRA &= ~(1 << ISC00);
            EIMSK |= (1 << INT0);
            break;

        case INT1:
            EIMSK &= ~(1 << INT1);
            EICRA |= (1 << ISC11);
            EICRA &= ~(1 << ISC10);
            EIMSK |= (1 << INT1);
            break;

        case INT2:
            EIMSK &= ~(1 << INT2);
            EICRA |= (1 << ISC21);
            EICRA &= ~(1 << ISC20);
            EIMSK |= (1 << INT2);
            break;
    }
}

void Bouton::attendreBas() 
{
    switch (interruption_)
    {
        case INT0:
            EIMSK &= ~(1 << INT0);
            EICRA &= ~((1 << ISC01) | (ISC00));
            EIMSK |= (1 << INT0);
            break;

        case INT1:
            EIMSK &= ~(1 << INT1);
            EICRA &= ~((1 << ISC11) | (ISC10));
            EIMSK |= (1 << INT1);
            break;
        
        case INT2:
            EIMSK &= ~(1 << INT2);
            EICRA &= ~((1 << ISC21) | (ISC20));
            EIMSK |= (1 << INT2);
            break;

    }
}