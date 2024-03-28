#pragma once 

#include <raylib.h>
#include "globals.h"

// TODO: remove static and add to grid.c instead
static Texture2D grid_texture;
static u32 grid_x;
static u32 grid_y;
static u32 grid_width;
static u32 grid_height;

void grid_init(void);
void grid_destroy(void);

void grid_set(u32 x, u32 y, u32 width, u32 height);
Vector2 get_grid_size(void);
void grid_update(void);
void grid_draw(void);
// TODO: implment toggle on/off for grid
