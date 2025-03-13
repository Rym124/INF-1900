#include "classUART.h"
#include "debug.h"

void printf(uint16_t valeur) {
    static UART uart;
    uart.transmissionVariable(valeur);
}

void printf( char* message) {
    static UART uart;
    uart.transmissionParBit(message);
}