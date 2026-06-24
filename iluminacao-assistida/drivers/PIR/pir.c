#include <msp430.h>
#include "pir.h"
#include "light_stages.h"

void init_pir() {
    P1DIR &= ~BIT3;   //configura P1.3 como entrada
    P1IES &= ~BIT3;   //ativa interrupção na borda de subida
    P1IFG &= ~BIT3;   //limpa a flag por segurança antes de ligar
    P1IE  |=  BIT3;   //habilita interrupcao local do pino 1.3
}

#pragma vector=PORT1_VECTOR
__interrupt void PIR_activated(void) {
    switch (P1IV) {
        case 0x08:                           //ativação do P1.3, limpa a flag automaticamente
            init_fade_in();
            break;
        default:
            break;
    }
}
