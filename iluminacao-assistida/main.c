#include <msp430.h>
#include "light_stages.h"
#include "drivers/TIMERS/Timer_A1/timer_A1.h"
#include "drivers/TIMERS/Timer_B0/timer_B0.h"
#include "drivers/PIR/pir.h"
#include "drivers/LCD/lcd.h"

void main() {
    WDTCTL = WDTPW | WDTHOLD;

    init_pir();                             //configurações inciais do sensor de movimento
    init_light_stages();                    //inicia a logica de estados da iluminação
    init_timer_A1();                        //configurações do timer A1 que controla o PWM que controla a iluminação do LED via hardware
    init_timer_B0();                        //conigurações do timer B0 que atualiza o light stage a cada 1ms e levanta a flag do lcd a cada 250ms
    lcdInit();

    __enable_interrupt();
    
    while(1) {
        if(update_lcd_flag) {
            update_lcd_flag = 0;

            lcdWriteByte(0x80, 0);          //reseta o cursor das linhas do lcd

            unsigned int porcentagem = ((unsigned long)TA1CCR1 * 100) / TA1CCR0; 

            unsigned char centena = (porcentagem / 100) % 10;
            unsigned char dezena  = (porcentagem / 10) % 10;
            unsigned char unidade = porcentagem % 10;
            
            char texto_tela[6] = {0}; 
            int i = 0;
            
            if (centena > 0) {
                texto_tela[i] = centena + '0';
                i++;
            }
            texto_tela[i++] = dezena + '0';
            texto_tela[i++] = unidade + '0';
            texto_tela[i++] = '%';
            texto_tela[i++] = ' ';
            texto_tela[i] = '\0';   

            lcdWriteChar(texto_tela);
        }

        __low_power_mode_0();
    }
}
