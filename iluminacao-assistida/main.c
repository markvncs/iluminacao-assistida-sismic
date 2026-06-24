#include <msp430.h>
#include "light_stages.h"
#include "drivers/TIMERS/Timer_A1/timer_A1.h"
#include "drivers/TIMERS/Timer_B0/timer_B0.h"
#include "drivers/PIR/pir.h"

void main() {
    WDTCTL = WDTPW | WDTHOLD;

    BCSCTL1 = CALBC1_1MHZ;                              // configura a faixa básica do DCO para 1MHz
    DCOCTL = CALDCO_1MHZ;                               // aplica o ajuste fino de calibração de fábrica

    init_pir();
    init_light_stages();
    init_timer_A1();
    init_timer_B0();

    __enable_interrupt();
    __low_power_mode_0();
    
    while(1) {}
}