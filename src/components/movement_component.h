#pragma once

#include "../utils/defines.h"

typedef struct movement_component {
    f32 current_speed;     // Entity's current speed
    f32 speed_multiplier;  // Entity's speed multiplier
    f32 max_speed;         // Entity's maximum speed
    f32 acceleration;      // Entity's acceleration
    f32 deceleration;      // Entity's deceleration
    f32 dx;                // Entity's x movement delta
    f32 dy;                // Entity's y movement delta
    f32 last_dx;           // Entity's last x movement delta
    f32 last_dy;           // Entity's last y movement delta
} movement_component;
