#include <avr/io.h>
#define F_CPU 8000000
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdint.h>

// Rym Fortas et Marily Lemire

volatile uint8_t gMinuterieExpiree = 0;

volatile uint8_t gBoutonPoussoir = 0;

void initialisation()
{

    cli();
    DDRD &= ~(1 << PD2); // PD2 bouton
    PORTA |= (1 << PD2);

    DDRA |= (1 << PA0) | (1 << PA1); // led

    EIMSK |= (1 << INT0); // Activer l'interruption externe INT0

    EICRA |= (1 << ISC00); // any edge

    sei();
}

ISR(TIMER1_COMPA_vect)
{

    gMinuterieExpiree = 1;
}

ISR(INT0_vect)
{

    gBoutonPoussoir = 1;

    // anti-rebond

    _delay_ms(30);
}

void partirMinuterie(uint16_t duree)
{

    gMinuterieExpiree = 0;

    // mode CTC du timer 1 avec horloge divisée par 1024

    // interruption après la durée spécifiée

    TCNT1 = 0;

    OCR1A = duree;

    TCCR1A = 0;

    TCCR1B = (1 << WGM12) | (1 << CS12) | (1 << CS10); // ctc prescaler 1024

    TCCR1C = 0;

    TIMSK1 = (1 << OCIE1A);
}

bool buttonPressed()
{
    return (PIND & (1 << PD2));
}

void allumeRouge()
{
    PORTA |= (1 << PA0);
    PORTA &= ~(1 << PA1);
}

void eteindre()
{
    PORTA &= ~(1 << PA0);
    PORTA &= ~(1 << PA1);
}

void clignoteRouge()
{
    for (uint8_t i = 0; i < 2; i++) // 2 cycles de 25 = 100
    {
        allumeRouge();
        _delay_ms(25);
        eteindre();
        _delay_ms(25);
    }
}

void allumeVert()
{
    PORTA &= ~(1 << PA0);
    PORTA |= (1 << PA1);
}

int main()
{

    initialisation();

    _delay_ms(10000); // 10 secondes
    clignoteRouge();
    eteindre();

    gBoutonPoussoir = 0;

    partirMinuterie(7812); // 1 sec = 8000000/1024

    do
    {

    } while (gMinuterieExpiree == 0 && gBoutonPoussoir == 0);

    cli();

    if (gBoutonPoussoir)
    {
        allumeVert(); // Winner
    }
    else
    {
        allumeRouge(); // Loser
    }
    while (1)
        ;
}
