#include "del.h"

void delaiMS(uint16_t delai) {
    for(uint16_t i = 0; i < delai; i++) {
        _delay_ms(1);
    }
}

DEL::DEL(uint8_t bornePositive, uint8_t borneNegative, volatile uint8_t* ddr, volatile uint8_t* port) : 
    bornePositive_(bornePositive), borneNegative_(borneNegative), port_(port), ddr_(ddr) {

    *ddr_ |= (1 << bornePositive_) | (1 << borneNegative_);
}

DEL::DEL() : bornePositive_(PB3), borneNegative_(PB4), port_(&PORTB), ddr_(&DDRB) {
    *ddr_ |= (1 << bornePositive_) | (1 << borneNegative_);
}

void DEL::allumerRouge() {
    *port_ |= (1 << bornePositive_);
    *port_ &= ~(1 << borneNegative_);
}
void DEL::allumerVert() {

    *port_ &= ~(1 << bornePositive_);
    *port_ |= (1 << borneNegative_);
}
void DEL::allumerAmbre() {
    allumerRouge();
    _delay_ms(DELAI_AMBRE_MS);
    allumerVert();
    _delay_ms(DELAI_AMBRE_MS);
}
bool DEL::utiliseTimer0() {
    return {
        // Vérifie si le compteur du Timer0 est en marche
        ((TCCR0B & ((1 << CS02) | (1 << CS01) | (1 << CS00))) != 0x0) && 
        // Vérfie si Timer0 utilise les OC0X
        ((TCCR0A & ((1 << COM0A0) | (1 << COM0A1) | (1 << COM0B0) | (1 << COM0B1))) != 0x0) && 
        // Vérifie si les bornes sont à PB3 et PB4
        ((borneNegative_ == PB4 || borneNegative_ == PB3) && (bornePositive_ == PB4 || bornePositive_ == PB3)) &&
        port_ == &PORTB
    };
}
void DEL::eteindre() {
    if (utiliseTimer0()) {
        TCCR0B &= ~((1 << CS00) | (1 << CS01) | (1 << CS02));
        TCCR0A &= ~((1 << COM0A0) | (1 << COM0A1) | (1 << COM0B0) | (COM0B1));
    }

    *port_ &= ~(1 << bornePositive_);
    *port_ &= ~(1 << borneNegative_);
}

// Clignotement en fonction de la durée (fréquence fixe à 2 Hz)

void DEL::clignoterVert(uint16_t dureeMs) {
    uint16_t nombreFois = FREQUENCE_CLIGNOTEMENT_HZ * dureeMs / 1000;
    clignoterVert(nombreFois, FREQUENCE_CLIGNOTEMENT_HZ);
}
void DEL::clignoterRouge(uint16_t dureeMs) {
    uint16_t nombreFois = FREQUENCE_CLIGNOTEMENT_HZ * dureeMs / 1000;
    clignoterRouge(nombreFois, FREQUENCE_CLIGNOTEMENT_HZ);
}

// Clignotement en fonction du nombre et de la fréquence

void DEL::clignoterVert(uint8_t nombreFois, uint16_t frequence){
    uint16_t periode_ms = 1000 / frequence;
    for (uint16_t i = 0; i < nombreFois; i++) {
        allumerVert();
        delaiMS(periode_ms/2);
        eteindre();
        delaiMS(periode_ms/2);
    }
}
void DEL::clignoterRouge(uint8_t nombreFois, uint16_t frequence) {
    uint16_t periode_ms = 1000 / frequence;
    for (uint8_t i = 0; i < nombreFois; i++) {
        allumerRouge();
        delaiMS(periode_ms/2);
        eteindre();
        delaiMS(periode_ms/2);
    }
}

// Utilise le Timer0 (Marche uniquement avec OC0A et OC0B)

void DEL::allumerAmbreT() {
    *port_ |= (1 << borneNegative_);
    *port_ &= ~(1 << bornePositive_);

    uint16_t prescaler = 1024;
    uint16_t nombreCycleCpu = DELAI_AMBRE_MS * F_CPU / 1000;


    TCNT0 = 0;

    // Compare Output Mode: Toggle (OC0A et OC0B) et Mode d'opération: CTC
    TCCR0A &= ~(1 << COM0A1);
    TCCR0A |= (1 << COM0A0) | (1 << WGM01);
    TCCR0A &= ~(1 << COM0B1);
    TCCR0A |= (1 << COM0B0);

    OCR0A = nombreCycleCpu / prescaler;
    OCR0B = nombreCycleCpu / prescaler;

    // Prescaler: 1024
    TCCR0B |= (1 << CS02) | (1 << CS00);
    TCCR0B &= ~(1 << CS01);

}