#include <msp430.h>
#include "timer_A1.h"

void timerA1Init(void) {
    TA1CTL = TASSEL__SMCLK | MC__UP | TACLR;            // sera utilizada uma frequencia de 1KHz
    
    TA1CCR0 = 1000 - 1;
}
