#include <avr/io.h>
#define F_CPU 8000000UL
#include <util/delay.h>
#include <avr/interrupt.h>
#include "can.h"
#include "affichagememoire.h"
#include "UART.hpp"

//#inlcude le fichier des ledcontrollers de jonathan

#define VOLTAGE_THRESHOLD_HIGH 230
#define VOLTAGE_THRESHOLD_LOW 50
#define TWO 2

    
    class Sensor {
        private:
        LedController led; //fonction de jonathan
        UART uart; 
        can adc; // inclure le fichier can
    
        public:
            void run() {
                while (true) {
                    uint16_t voltage = adc.lecture(0) >> TWO;
                    if (voltage >= VOLTAGE_THRESHOLD_HIGH) {
                        led.turnRedLedOn();
                    } else if (voltage <= VOLTAGE_THRESHOLD_LOW) {
                        led.turnGreenLedOn();
                    } else {
                        led.turnAmberLedOn();
                    }
                    uart.transmission(voltage); // pour laffichage sur le terminal on peut lenlever
                }
            }
    };
    