#include <msp430.h>
#include "lcd.h"
#include "i2c.h"

static lcdWriteNibble(uint8_t nibble, uint8_t isChar) {
    uint8_t pack = 0;
    
    pack |= (nibble << 4) | isChar;        //posicionando nibble dm D[4:7] e RS em P0

    pack |= (1 << 3);

    pack &= ~(1 << 1);                      //posicionando R/W = 0 em P1
    pack &= ~(1 << 2);                      //posicionando E = 0 em P2

    i2cSend(0x3F, pack);

    pack |= (1 << 2);                        //posicionando E = 1 em P2

    i2cSend(0x3F, pack);

    pack &= ~(1 << 2);                      //posicionando E = 0 em P2

    i2cSend(0x3F, pack);
}

static lcdWriteByte(uint8_t byte, uint8_t isChar) {
    uint8_t hn = byte >> 4;
    uint8_t ln = byte & 0x0F; 

    lcdWriteNibble(hn, isChar);

    lcdWriteNibble(ln, isChar);
}

void lcdWriteChar(char *str) {
    int cursor = 0;
    while(*str != 0x00){
        if(cursor == 16) {
            lcdWriteByte(0xC0, 0);  //trata a quebra de linha ao chegar em 0x0F na primeira linha do LCD, pulando pra linha 40 com a instrução 0x80 + 0x40 (mandar cursor para addr = 0x40)
            cursor = 0;
        }
        if(*str == '\n') {
            lcdWriteByte(0xC0, 0);  //trata quebra de linha ao se deparar com o caracter \n, aí pula pra linha 2 e passa pra proxima iteração com o proximo caracter
            str++;
            cursor = 0;
            continue;
        }

        lcdWriteByte(*str, 1);

        str++;
        cursor++;
    }
}

void lcdInit(void) {
    __delay_cycles(20000);

    lcdWriteNibble(0x03, 0);
    __delay_cycles(5000);
    
    lcdWriteNibble(0x03, 0);
    __delay_cycles(150);

    lcdWriteNibble(0x03, 0);            //estado conhecido -> modo 8 bits
    __delay_cycles(50);

    lcdWriteNibble(0x02, 0);            //modo 4 bits
    __delay_cycles(50);


    lcdWriteByte(0x28, 0); // Function Set: 4 bits, 2 linhas, fonte 5x8
    __delay_cycles(50);
    lcdWriteByte(0x0C, 0); // Display ON, Cursor OFF, Blink OFF
    __delay_cycles(50);
    lcdWriteByte(0x01, 0); // Clear Display (Limpa a tela)
    __delay_cycles(2000);  // Comando de limpar exige mais tempo!
    lcdWriteByte(0x06, 0); // Entry Mode Set: Incremento automático do cursor
    __delay_cycles(50);
}
