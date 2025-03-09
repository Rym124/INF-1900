#include <avr/io.h>
#define F_CPU 8000000
#include <util/delay.h>
#include <avr/interrupt.h>

enum ModeDeclenchement {MONTANT, DESCENDANT, FRONT, BAS};

class InterruptionExterne {
public:
    // Construit un gestionnaire d'interruption pour l'interruption demandée, par défaut utilise le mode de déclenchment FRONT (Any Edge)
    InterruptionExterne(uint8_t interruption);
    // Construit un gestionnaire d'interruption pour l'interruption demandée avec mode de déclenchement demandé
    InterruptionExterne(uint8_t interruption, ModeDeclenchement mode);
    // Construit un gestionnaire d'interruption pour l'interruption INT0, par défaut utilise le mode de déclenchement FRONT (Any Edge)
    InterruptionExterne();

    // Modifie le mode de déclenchement à MONTANT (Front Montant)
    void attenteFrontMontant();
    // Modifie le mode de déclenechement à DESCENDANT (Front Descendant)
    void attenteFrontDescendant();
    // Modifie le mode de déclenchement à FRONT (Any Edge)
    void attenteFront();
    // Modifie le mode de déclenchement à BAS (Niveau Bas)
    void attenteBas();

private:
    uint8_t interruption_;
};
