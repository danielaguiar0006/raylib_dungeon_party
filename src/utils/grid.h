#pragma once 

#include <raylib.h>
#include "globals.h"

// TODO: remove static and add to grid.c instead
static Texture2D grid_texture;
static u32 grid_x;
static u32 grid_y;
static u32 grid_width;
static u32 grid_height;

void init_grid(void);
void destroy_grid(void);

void set_grid(u32 x, u32 y, u32 width, u32 height);
Vector2 get_grid_size(void);
void update_grid(void);
void draw_grid(void);
// TODO: implment toggle on/off for grid
