#include <msp430.h>
#include "i2c.h"
#include "lcd.h"

void main() {
    WDTCTL = WDTPW | WDTHOLD;

    BCSCTL1 = CALBC1_1MHZ;                              // configura a faixa básica do DCO para 1MHz
    DCOCTL = CALDCO_1MHZ;                               // aplica o ajuste fino de calibração de fábrica

    i2cInit();
    lcdInit();
    
    while(1) {}
}