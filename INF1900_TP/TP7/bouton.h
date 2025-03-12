#include <avr/io.h>
#define F_CPU 8000000
#include <util/delay.h>
#include <avr/interrupt.h>
#define AUCUNE_INTERRUPTION 3
#define DELAI_ANTI_REBOND 10

enum ModeDeclenchement {MONTANT, DESCENDANT, FRONT, BAS};
enum class Port {A, B, C, D};

class Bouton {
public:

    // Construit un gestionnaire de bouton avec l'interruption et le mode de déclenchement demandés
    Bouton(uint8_t interruption, ModeDeclenchement mode);

    // Construit un gestionnaire de bouton avec l'interruption demandé (Mode de déclenchement à FRONT (Any Edge))
    Bouton(uint8_t interruption);

    // Construit un gestionnaire de bouton à la broche demandée
    Bouton(Port port, uint8_t pin);

    // Active les interruption d'un bouton si le microcontrôleur le permet
    void activerInterruption(ModeDeclenchement mode);

    // Désactive les interruption d'un bouton si le microcontrôleur permet l'interruption
    void desactiverInterruption();

    // Indique si ou un bouton est appuyé ou non (par scrutation)
    bool estAppuye();


private:
    // Modifie le mode de déclenchement à MONTANT (Front Montant)
    void attenteFrontMontant();
    // Modifie le mode de déclenechement à DESCENDANT (Front Descendant)
    void attenteFrontDescendant();
    // Modifie le mode de déclenchement à FRONT (Any Edge)
    void attenteFront();
    // Modifie le mode de déclenchement à BAS (Niveau Bas)
    void attenteBas();

    uint8_t interruption_;
    bool utiliseInterruption_;
    Port port_;
    uint8_t pin_;
    

};