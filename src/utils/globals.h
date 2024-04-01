#pragma once

#include "defines.h"

// Change for more or less total entities
#define GLOBAL_MAX_ENTITIES 1024     // HACK: extern const not working using #define instead
extern const u16 TILE_SCALE_FACTOR;  // TILE_SIZE_PX * TILE_SCALE_FACTOR = 1 tile
extern const u16 TILE_SIZE_PX;       // NUMxNUM (e.g. 16x16) pixels
extern const u8 MAX_TAG_LENGTH;      // Max length of a tag for the tag component
extern f32 global_time_scale;
extern u16 window_width;
extern u16 window_height;

// TODO: still needs to be implemented:
// extern float FRICTION_FACTOR;
// extern Color BACKGROUND_COLOR;
// extern float CAMERA_ZOOM_FACTOR;
// extern bool IS_PAUSED;
// extern bool IS_FULLSCREEN;
// extern bool RELATIVE_CAMERA_ZOOM;
