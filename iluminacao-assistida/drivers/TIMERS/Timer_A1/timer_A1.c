#include <msp430.h>
#include "timer_A1.h"

void init_timer_A1(void) {
    P2DIR |= BIT0;                                      //p2.0 definido como saída
    P2SEL |= BIT0;                                      //p2.0 é saida do sinal do timer A1.1

    TA1CTL = TASSEL__SMCLK | MC__UP | TACLR;            //sera utilizada uma frequencia de 1KHz ; CCR0 = SMCLK / 1000 = 1000 - 1
    
    TA1CCR0 = 1000 - 1;

    TA1CCTL1 = OUTMOD_7;                                //reset em ccr1 e set em ccr0

    TA1CCR1 = 0;
}
