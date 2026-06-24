#include <msp430.h>
#include "light_stages.h"
#include "timer_A1.h"

enum Stages stage;
volatile unsigned int counter;

void init_light_stages(void) {
    stage = OFF;                //estado da iluminação inicia em OFF
    counter = 0;                //contador do freio de software inicia em 0
    TA1CCR1 = 0;                //duty cycle inicia em 0
}

void init_fade_in(void) {
    stage = FADE_IN;
}

void update_light_stage(void) {
    switch(stage) {
        case OFF:
            break;
            
        case FADE_IN:
            counter++;                          //inicia a logica de contagem. o counter só atualiza o TA1CCR1 qnd chega em 2000 (para gerar a demora na contagem sem usar delay cycles)
            
            if(counter == 2000) {                  
                counter = 0;
                TA1CCR1 += 1;

                if(TA1CCR1 == TA1CCR0) {
                    stage = ON;                 //quando chegar no teto de iluminação (TA1CCR0), stage = ON
                }
            }

            break;

        case ON:
            break;

        case FADE_OUT:
            break;
    }
}