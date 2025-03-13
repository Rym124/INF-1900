#include <avr/io.h>
#ifndef CLASS_UART
#define CLASS_UART
#define F_CPU 8000000
#include <util/delay.h>

class UART {
public:
    // Constructeur pour initialiser le port UART
    UART();
    void transmissionParOctet(char );
    void transmissionParBit( char* );
    void transmissionVariable(uint16_t );
    
};

#endif