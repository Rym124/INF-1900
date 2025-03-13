#include "bouton.h"

Bouton::Bouton(uint8_t interruption, ModeDeclenchement mode) : interruption_(interruption), utiliseInterruption_(true)
{
    cli();
    switch (interruption)
    {
        case INT0:
            if (mode == MONTANT) {
                EICRA |= (1 << ISC01) | (1 << ISC00);
            }
            else if (mode == DESCENDANT) {
                EICRA |= (1 << ISC01);
                EICRA &= ~(1 << ISC00);
            }
            else if (mode == FRONT) {
                EICRA &= ~ (1 << ISC01);
                EICRA |= (1 << ISC00);
            }
            else if (mode == BAS) {
                EICRA &= ~((1 << ISC00) | (1 << ISC01));
            }

            EIMSK |= (1 << INT0);
            port_ = Port::D;
            pin_ = PD2;
            break;
        
        case INT1:
            if (mode == MONTANT) {
                EICRA |= (1 << ISC11) | (1 << ISC10);
            }

            else if (mode == DESCENDANT) {
                EICRA |= (1 << ISC11);
                EICRA &= ~(1 << ISC10);
            }

            else if (mode == FRONT) {
                EICRA &= ~(1 << ISC11);
                EICRA |= (1 << ISC10);
            }

            else if (mode == BAS) {
                EICRA &= ~((1 << ISC11) | (1 << ISC10));
            }

            EIMSK |= (1 << INT1);
            port_ = Port::D;
            pin_ = PD3;
            break;

        case INT2:
            if (mode == MONTANT) {
                EICRA |= (1 << ISC21) | (1 << ISC20);
            }

            else if (mode == DESCENDANT) {
                EICRA |= (1 << ISC21);
                EICRA &= ~(1 << ISC20);
            }

            else if (mode == FRONT) {
                EICRA &= ~ (1 << ISC21);
                EICRA |= (1 << ISC20);
            }

            else if (mode == BAS) {
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
            attenteFront();
            break;
        case MONTANT:
            attenteFrontMontant();
            break;
        case DESCENDANT:
            attenteFrontDescendant();
            break;
        case BAS:
            attenteBas();
            break;
        
        default:
            break;
    }
}

void Bouton::desactiverInterruption() 
{
    if (utiliseInterruption_) {
        EIMSK &= ~(1 << interruption_);
        utiliseInterruption_ = false;
    }
}

bool Bouton::estAppuye() 
{
    _delay_ms(DELAI_ANTI_REBOND);

    if(port_ == Port::A) {
        return (PINA & (1 << pin_));
    }

    else if(port_ == Port::B) {
        return (PINB & (1 << pin_));
    }

    else if(port_ == Port::C) {
        return (PINC & (1 << pin_));
    }

    else if(port_ == Port::D) {
        return (PIND & (1 << pin_));
    }

    return false;
}


void Bouton::attenteFront() {
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

void Bouton::attenteFrontMontant() {
    switch(interruption_) {
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

void Bouton::attenteFrontDescendant() {
    switch (interruption_) {
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

void Bouton::attenteBas() {
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