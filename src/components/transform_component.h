#pragma once

#include "raylib.h"            // Vector2
#include "../utils/globals.h"  // TILE_SCALE_FACTOR 
#include "../utils/defines.h"

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

Vector2 get_transform_midpoint(transform_component* component);
//TODO: void set_transform(transform_component* component, f32 x, f32 y, f32 grid_x, f32 grid_y, f32 width, f32 height, f32 rotation, u16 scale);
