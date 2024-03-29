#include "grid.h"

void init_grid(void) {
    grid_texture = LoadTexture("assets/textures/grid.png");
    grid_x = 0;
    grid_y = 0;
    //  gridWidth = static_cast<int>((WINDOW_WIDTH / CAMERA_ZOOM_FACTOR) / (TILE_WIDTH * TILE_SCALE_FACTOR));
    grid_width = (u32)(window_width / (TILE_SIZE_PX * TILE_SCALE_FACTOR));
    grid_width = (u32)(window_height / (TILE_SIZE_PX * TILE_SCALE_FACTOR));
}

void destroy_grid(void) {
    UnloadTexture(grid_texture);
}

void set_grid(u32 x, u32 y, u32 width, u32 height) {
    grid_x = x;
    grid_y = y;
    grid_width = width;
    grid_height = height;
}

Vector2 get_grid_size(void) {
    return (Vector2) { (float)grid_width, (float)grid_height };
}

void update_grid(void) {
    // Update grid count based on window size and camera zoom
    grid_width = (u32)(window_width / (TILE_SIZE_PX * TILE_SCALE_FACTOR));
    grid_height = (u32)(window_height / (TILE_SIZE_PX * TILE_SCALE_FACTOR));
}

void draw_grid(void) {
    for (u32 x = 0; x < grid_width; x++) {
        for (u32 y = 0; y < grid_height; y++) {
            Vector2 grid_position = (Vector2){ (float)(x * TILE_SIZE_PX * TILE_SCALE_FACTOR), (float)(y * TILE_SIZE_PX * TILE_SCALE_FACTOR) };
            DrawTextureEx(grid_texture, grid_position, 0, (float)TILE_SCALE_FACTOR, WHITE);
        }
    }
}
