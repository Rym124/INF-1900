#include "del.h"

void delaiMS(uint16_t delai) {
    for(uint16_t i = 0; i < delai; i++) {
        _delay_ms(1);
    }
}

DEL::DEL(uint8_t bornePositive, uint8_t borneNegative, volatile uint8_t* ddr, volatile uint8_t* port) : 
    bornePositive_(bornePositive), borneNegative_(borneNegative), port_(port), ddr_(ddr) {

    *ddr |= (1 << bornePositive_) | (1 << borneNegative_);
}

DEL::DEL() : bornePositive_(PB1), borneNegative_(PB0), port_(&PORTB), ddr_(&DDRB) {
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
void DEL::eteindre() {
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