#include <msp430.h>
#include "drivers/I2C/i2c.h"

void i2cInit(void) {
    UCB0CTL1 |= UCSWRST; 

    UCB0CTL0 = UCMST | UCMODE_3 | UCSYNC;        //mestre, modo i2c

    UCB0CTL1 |= UCSSEL__SMCLK;

    UCB0BR0 = 10;
    UCB0BR1 = 0;

    P3SEL |= BIT0 | BIT1;
    P3REN |= BIT0 | BIT1;
    P3OUT |= BIT0 | BIT1;

    UCB0CTL1 &= ~UCSWRST;
}

uint8_t i2cSendByte(uint8_t addr, uint8_t data) {
    UCB0IFG &= ~UCNACKIFG;                           //limpando nack antes de ler

    UCB0I2CSA = addr;                               //endereço do escravo
    UCB0CTL1 |= UCTR | UCTXSTT;                      //transmissor e start
        
    while(!(UCB0IFG & UCTXIFG));                      //espera o buffer de transmissão ficar vazio (TXIFG = 1)
    UCB0TXBUF = data;

    while(UCB0CTL1 & UCTXSTT);                      //espera o ciclo de acknowledge, que ocorre quando uctxstt = 0 (trava enqt uctxstt = 1)

    if(!(UCB0IFG & UCNACKIFG)) {                    //se o escravo responder com acknowledge, entra no caso:
        while(!(UCB0IFG & UCTXIFG));                  //espera o data ser transmitido
    }

    UCB0CTL1 |= UCTXSTP;                            //transmite stop
    while(UCB0CTL1 & UCTXSTP);                      //espera o stop ser transmitido

    if(UCB0IFG & UCNACKIFG) {                       //retorna 0 se houve ACK e 1 se houve NACK
        return 1;
    } else {
        return 0;
    }
}