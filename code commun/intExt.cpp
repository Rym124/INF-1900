#include "intExt.h"

InterruptionExterne::InterruptionExterne(uint8_t interruption, ModeDeclenchement mode) : interruption_(interruption) {
    cli();
    switch (interruption)
    {
    //                      ISCn1   ISCn0
    // Front montant:       1       1 
    // Front descendant:    1       0
    // Front:               0       1
    // Bas:                 0       0
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
        break;
    }
    sei();
}
InterruptionExterne::InterruptionExterne(uint8_t interruption) : InterruptionExterne(interruption, FRONT) {}
InterruptionExterne::InterruptionExterne() : InterruptionExterne(INT0, FRONT) {}
void InterruptionExterne::attenteFrontMontant() {
    // EICRA = ... ;
    //                      ISCn1   ISCn0
    // Front montant:       1       1 
    // Front descendant:    1       0
    // Front:               0       1
    // Bas:                 0       0
    cli();
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
    sei();
}
void InterruptionExterne::attenteFrontDescendant() {
    // EICRA = ... ;
    //                      ISCn1   ISCn0
    // Front montant:       1       1 
    // Front descendant:    1       0
    // Front:               0       1
    // Bas:                 0       0

    cli();
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
    sei();
}
void InterruptionExterne::attenteFront() {
    // EICRA = ... ;
    //                      ISCn1   ISCn0
    // Front montant:       1       1 
    // Front descendant:    1       0
    // Front:               0       1
    // Bas:                 0       0

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
void InterruptionExterne::attenteBas() {
    // EICRA = ... ;
    //                      ISCn1   ISCn0
    // Front montant:       1       1 
    // Front descendant:    1       0
    // Front:               0       1
    // Bas:                 0       0
    cli();
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
    sei();
}