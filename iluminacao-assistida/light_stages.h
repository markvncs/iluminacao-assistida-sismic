#ifndef LIGHT_STAGES_H_
#define LIGHT_STAGES_H_

enum Stages {
    OFF,
    FADE_IN,
    ON,
    FADE_OUT
};

void init_light_stages(void);
void init_fade_in(void);
void update_light_stage(void);

#endif