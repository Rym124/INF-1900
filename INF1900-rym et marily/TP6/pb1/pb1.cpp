#include <avr/io.h>
#define F_CPU 8000000
#include <util/delay.h>
#include <avr/interrupt.h>

// Rym Fortas et Marily Lemire

enum class etatLed
{
    ATTENTE,
    COMPTEUR,
    CLIGNOTE_VERT,
    CLIGNOTE_ROUGE,
    VERT,
};

volatile bool estAppuye = false;

volatile etatLed etat_present = etatLed::ATTENTE;

volatile uint8_t gCounter = 0;
volatile uint8_t gMinuterieExpiree = 0;
volatile uint8_t gBoutonPoussoir = 0;

ISR(INT0_vect)
{
    _delay_ms(30);

    estAppuye = !(PIND & (1 << PD2)); 


    EIFR |= (1 << INTF0);
}

void compteur()
{
    gCounter = 0;

    TCNT1 = 0;

    OCR1A = 781;

    TCCR1A = 0;

    TCCR1B = (1 << WGM12) | (1 << CS12) | (1 << CS10);

    TCCR1C = 0;

    TIMSK1 = (1 << OCIE1A);
}

void arretCompteur()
{
    TIMSK1 = 0;
}

ISR(TIMER1_COMPA_vect)
{
    gCounter += 1;
    if (gCounter == 120)
    {
        gMinuterieExpiree = 1;
        TIMSK1 = 0;
    }
}

void initialisation()
{
    cli();

    DDRB |= (1 << PB0);
    DDRB |= (1 << PB1);
    DDRD &= ~(1 << PD2);

    EIMSK |= (1 << INT0);

    EICRA |= (1 << ISC00); 

    sei();
}

void eteinte()
{
    PORTB &= ~(1 << PB0);
    PORTB &= ~(1 << PB1);
}

void allumeVert()
{
    PORTB &= ~(1 << PB0);
    PORTB |= (1 << PB1);
}

void clignoteVert()
{
    for (int i = 0; i < 5; i++)
    {
        allumeVert();
        _delay_ms(50);
        eteinte();
        _delay_ms(50);
    }
}

void allumeRouge()
{
    PORTB |= (1 << PB0);
    PORTB &= ~(1 << PB1);
}

void clignoteRouge()
{

    for (int i = 0; i < (gCounter / 2); i++)
    {
        allumeRouge();
        _delay_ms(250);
        eteinte();
        _delay_ms(250);
    }
}

void allumeVertUneSeconde()
{

    allumeVert();
    eteinte();
}

int main()
{
    

    initialisation();

        
    gBoutonPoussoir = 0;
   
    while (true)
    {
        switch (etat_present)
        {
        case etatLed::ATTENTE:
            if (estAppuye)
            {
                compteur();
                etat_present = etatLed::COMPTEUR;
            }
            break;

        case etatLed::COMPTEUR:

            if (!estAppuye)
            {
                arretCompteur();
                etat_present = etatLed::CLIGNOTE_VERT;
            }
            if (gMinuterieExpiree == 1)
                etat_present = etatLed::CLIGNOTE_VERT;
            break;

        case etatLed::CLIGNOTE_VERT:
            clignoteVert(); 
            _delay_ms(2000);
            etat_present = etatLed::CLIGNOTE_ROUGE;
            break;

        case etatLed::CLIGNOTE_ROUGE:
            clignoteRouge();
            etat_present = etatLed::VERT;
            break;

        case etatLed::VERT:
            allumeVertUneSeconde();
            etat_present = etatLed::ATTENTE;
            break;
        }
    }
}
