#include <msp430.h>
#include "i2c.h"
#include "lcd.h"

void main() {
    WDTCTL = WDTPW | WDTHOLD;
    
    i2cInit();
    lcdInit();
    
    while(1) {}
}