#pragma once

#include <raylib.h>           // Vector2
#include "../core/globals.h"  // TILE_SCALE_FACTOR 
#include "../utils/defines.h"
#include "../core/logger.h"

typedef struct transform_component {
    f32 x;
    f32 y;
    f32 grid_x;
    f32 grid_y;
    f32 width;
    f32 height;
    f32 rotation;
    u16 scale;
} transform_component;

// TODO: docs
Vector2 get_transform_midpoint(transform_component* component);
void set_transform_position_pixels(transform_component* component, f32 x, f32 y);
void set_transform_position_grid(transform_component* component, f32 x, f32 y);
