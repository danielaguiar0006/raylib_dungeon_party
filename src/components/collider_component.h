#pragma once

#include "../utils/defines.h"
#include "../core/logger.h"

typedef struct collider_component {
    f32 x;
    f32 y;
    f32 width;
    f32 height;
    f32 scale;
    b8 is_colliding;
} collider_component;
