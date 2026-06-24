#include <msp430.h>
#include "pir.h"

void init_pir() {
    P1DIR &= ~BIT3;
    P1IES &= ~BIT3;   //ativa interrupção na borda de subida
    P1IFG &= ~BIT3;
    P1IE  |=  BIT3;   //habilita interrupcao local do pino 1.3
}

#pragma vector=PORT1_VECTOR
_interrupt void PIR_activated(void) {
    switch (P1IV) {
        case 0x08:                           //ativação do P1.3, limpa a flag automaticamente
            init_fade_in();
    }
}