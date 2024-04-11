#pragma once

#include "../components/component_manager.h"
#include "../utils/defines.h"
#include "../core/globals.h"
#include "global_input.h"
#include "../entities/player_entity.h"
#include <math.h>  // fmaxf, fminf

void init_player_actions(void);
void update_player_actions(f32 delta_time);
