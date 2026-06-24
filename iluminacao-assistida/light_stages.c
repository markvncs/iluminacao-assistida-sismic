#include <msp430.h>
#include "light_stages.h"
#include "drivers/TIMERS/Timer_A1/timer_A1.h"

enum Stages stage;
volatile unsigned int counter;
volatile unsigned long time_on;

void init_light_stages(void) {
    stage = OFF;                         //estado da iluminação inicia em OFF
    counter = 0;                        //contador do freio de software inicia em 0
    TA1CCR1 = 0;                        //duty cycle inicia em 0
}

void init_fade_in(void) {
    stage = FADE_IN;
    counter = 0;
    time_on = 0;
}

void update_light_stage(void) {
    switch(stage) {
        case OFF:
            break;
            
        case FADE_IN:
            counter++;                          //inicia a logica de contagem. o counter só atualiza o TA1CCR1 qnd chega em 2000 (para gerar a demora na contagem sem usar delay cycles)
            
            if(counter == 10) {                  //a cada 10 ms incrementa o brilho         
                counter = 0;
                TA1CCR1 += 1;

                if(TA1CCR1 == TA1CCR0) {
                    stage = ON;                 //quando chegar no teto de iluminação (TA1CCR0), stage = ON
                }
            }
            break;

        case ON:
            time_on++;
            
            if(time_on == 30000) {            // 30000 ms = 30 segundos ligado antes do fade_out
                time_on = 0;
                stage = FADE_OUT;
            }
            break;

        case FADE_OUT:
            counter++;                          //inicia a logica de contagem. o counter só atualiza o TA1CCR1 qnd chega em 2 (para gerar a demora na contagem sem usar delay cycles)
    
            if(counter == 10) {                  //a cada 10 ms decrementa o brilho              
                counter = 0;
                TA1CCR1 -= 1;

                if(TA1CCR1 == 0) {
                    stage = OFF;                 //quando chegar no zero de imulimnação (0), stage = OFF
                }
            }
            break;
    }
}
