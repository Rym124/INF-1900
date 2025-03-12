#include <avr/io.h>
#ifndef CLASS_UART
#define CLASS_UART

class UART {
public:
    // Constructeur pour initialiser le port UART
    UART();
    void transmissionParOctet(char );
    void transmissionParBit(const char* );
    void transmissionVariable(uint16_t );
    
};

#endif