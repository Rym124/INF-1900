#include <avr/io.h>
#define F_CPU 8000000UL
#include <util/delay.h>
#include <avr/interrupt.h>
#include "can.h"
#include "affichagememoire.h"
//#inlcude le fichier des ledcontrollers de jonathan


class Sensor {
    private:
        LedController led;
        UART uart;
        can adc;
    
    public:
        void run();
    };
    