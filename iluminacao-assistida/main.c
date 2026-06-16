#include <msp430.h>

void main() {
    WDTCTL = WDTPW | WDTHOLD;
    
    while(1) {}
}