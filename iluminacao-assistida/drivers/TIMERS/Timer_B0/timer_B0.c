#include <msp430.h>
#include "timer_B0.h"
#include "light_stages.h"

void init_timer_B0(void) {

    TB0CTL = TBSSEL__SMCLK | MC__UP | TBCLR;            //sera utilizada uma frequencia de 1KHz ; CCR0 = SMCLK / 1000 = 1000 - 1

    TB0CCTL0 = CCIE;                                    //habilita interrupção local
    
    TB0CCR0 = 1000 - 1;                                 //gera 1ms por ciclo
}

#pragma vector=TIMER0_B0_VECTOR                      //interrupt vector addres do canal 0 do timer B0 (B0.0)
__interrupt void Timer_B0_ISR(void) {
    update_light_stage();
}
