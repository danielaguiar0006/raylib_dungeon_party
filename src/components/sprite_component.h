#pragma once

#include <raylib.h>

typedef struct sprite_component {
    Texture2D texture;           // Entity's texture
    Rectangle source_rectangle;  // Source rectangle
    Color tint;                  // Tint color
} sprite_component;
