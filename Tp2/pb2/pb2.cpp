#include <avr/io.h>
#define F_CPU 8000000
#include <util/delay.h>

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

bool buttonPressed()
{
    if (PIND & (1 << PD2))
    {
        _delay_ms(10);
        if (PIND & (1 << PD2))
        {
            return true;
        }
    }
    return false;
}

void allumeVert()
{

    PORTA &= ~(1 << PA0);
    PORTA |= (1 << PA1);
}

void allumeRouge()
{

    PORTA |= (1 << PA0);
    PORTA &= ~(1 << PA1);
}

void allumeAmbre()
{

    do
    {
        PORTA |= (1 << PA0);
        PORTA &= ~(1 << PA1);
        _delay_ms(5);
        PORTA |= (1 << PA1);
        PORTA &= ~(1 << PA0);
        _delay_ms(5);
    } while (buttonPressed());
}

void allumeRouge2()
{

    do
    {
        PORTA |= (1 << PA0);
        PORTA &= ~(1 << PA1);
    } while (buttonPressed());
}

void eteinte()
{
    PORTA &= ~(1 << PA0);
    PORTA &= ~(1 << PA1);
}

void allumeVert2()
{

    do
    {
        PORTA &= ~(1 << PA0);
        PORTA |= (1 << PA1);
    } while (buttonPressed());
}

int main()
{

    DDRA |= (1 << PA0);
    DDRA |= (1 << PA1);
    DDRD &= ~(1 << PD2);

    colourState etat_present = colourState::ROUGE;

    while (true)
    {
        bool resultat = buttonPressed();

        switch (etat_present)
        {
        case colourState::ROUGE:
            allumeRouge();
            if (resultat == true)
            {
                etat_present = colourState::AMBRE;
            }
            break;

        case colourState::AMBRE:
            allumeAmbre();
            etat_present = colourState::VERT;

            break;

        case colourState::VERT:
            allumeVert();
            if (buttonPressed())
            {
                etat_present = colourState::ROUGE2;
            }
            break;

        case colourState::ROUGE2:
            allumeRouge2();
            etat_present = colourState::OFF;
            break;

        case colourState::OFF:
            eteinte();
            if (buttonPressed())
            {
                etat_present = colourState::VERT2;
            }
            break;

        case colourState::VERT2:
            allumeVert2();
            etat_present = colourState::ROUGE;

            break;
        }
    }
}
