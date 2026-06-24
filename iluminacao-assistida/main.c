#include <msp430.h>
#include "i2c.h"
#include "lcd.h"

void main() {
    WDTCTL = WDTPW | WDTHOLD;

    BCSCTL1 = CALBC1_1MHZ;                              // configura a faixa básica do DCO para 1MHz
    DCOCTL = CALDCO_1MHZ;                               // aplica o ajuste fino de calibração de fábrica

    i2cInit();
    lcdInit();

    timerA1Init();
    init_light_stages();

    __enable_interrupt();
    
    while(1) {
        update_light_stage();
    }
}

#pragma vector = 47
_interrupt void PIR_activated(void) {
    switch (P1IV) {
        case 0x08:                           //ativação do P1.3, limpa a flag automaticamente
            init_fade_in();
    }
}