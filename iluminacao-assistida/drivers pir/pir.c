#include <msp430.h>
#include "pir.h"

void pirInit() {
    P1DIR &= ~BIT3;
    P1IES &= ~BIT3;   //ativa interrupção na borda de subida
    P1IFG &= ~BIT3;
    P1IE  |=  BIT3;   //habilita interrupcao local do pino 1.3
}