#pragma once

// Include all systems:
#include "update_entity_transforms.h"
#include "draw_sprites.h"
#include "global_input.h"
#include "player_actions.h"

void init_systems(void);
void update_systems(f32 delta_time);
void destroy_systems(void);
