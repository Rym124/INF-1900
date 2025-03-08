#include <avr/io.h>

class UART {
public:
    // Constructeur pour initialiser le port UART
    UART();

    // Fonction pour transmettre un octet par UART
    void transmission(unsigned char data);

private:
    // Fonction pour initialiser UART
    void initialisation();
};


