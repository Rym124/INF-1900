#include <avr/io.h>
#define F_CPU 8000000
#include <util/delay.h>

// Rym Fortas et Marily Lemire

// Tableau 1:
/*
Entrées: A0 et A1
Sortie: D2
+--------------+------------+------------+-----------+
| État présent | Entrée (A) | État futur | Sortie(Z) |
+--------------+------------+------------+-----------+
| INIT         | 1          | INIT       | 0         |
| INIT         | 0          | EA         | 0         |
| EA           | 1          | EA         | 0         |
| EA           | 0          | EB         | 0         |
| EB           | 1          | EB         | 1         |
| EC           | x          | INIT       | 0         |
+--------------+------------+------------+-----------+
*/

enum class ledState
{
    INIT,
    EA,
    EB,
    EC,
};
bool appuiye_ou_pas()
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

int main()
{

    DDRA |= (1 << PA0);
    DDRA |= (1 << PA1);
    DDRD &= ~(1 << PD2);

    ledState etat_present = ledState::INIT;
    while (true)
    {

        bool resultat = appuiye_ou_pas();
        switch (etat_present)
        {
        case ledState::INIT:
            PORTA &= ~(1 << PA0);
            PORTA &= ~(1 << PA1);
            if (resultat == true)
            {
                while (appuiye_ou_pas())
                    ;
                etat_present = ledState::EA;
            }

            break;

        case ledState::EA:
            PORTA &= ~(1 << PA0);
            PORTA &= ~(1 << PA1);
            if (resultat == true)
            {
                while (appuiye_ou_pas())
                    ;
                etat_present = ledState::EB;
            }

            break;

        case ledState::EB:
            PORTA &= ~(1 << PA0);
            PORTA &= ~(1 << PA1);
            if (resultat == true)
            {
                while (appuiye_ou_pas())
                    etat_present = ledState::EC;
            }
            break;

        case ledState::EC:
            PORTA |= (1 << PA0);
            PORTA &= ~(1 << PA1);

            _delay_ms(2000);
            etat_present = ledState::INIT;
            break;
        }
    }
}
