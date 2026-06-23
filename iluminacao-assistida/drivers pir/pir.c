#include <msp430.h>
#include "pir.h"

void pirInit() {
    P1DIR &= ~BIT3;
}