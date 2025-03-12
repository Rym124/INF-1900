#include <avr/io.h>
#define F_CPU 8000000
#include <util/delay.h>
#include "classUART.h"
#include "memoire_24.h"

int main()
{
   
    UART uart;
    while(1)
    uart.transmissionVariable(23);

}