#include "draw_sprites.h"

void draw_sprites(void) {
    for (u32 i = 0; i < GLOBAL_MAX_ENTITIES; i++) {
        if (active_components[i].active == TRUE &&
            has_component(i, COMPONENT_SPRITE) &&
            has_component(i, COMPONENT_TRANSFORM)) {

            DrawTextureEx(sprite_components[i].texture,
                (Vector2) {
                transform_components[i].x, transform_components[i].y
            },
                transform_components[i].rotation,
                transform_components[i].scale,
                sprite_components[i].tint);
        }
    }
}

void unload_sprites(void) {
    for (u32 i = 0; i < GLOBAL_MAX_ENTITIES; i++) {
        if (has_component(i, COMPONENT_SPRITE)) {
            // UnloadTexture() already checks if the texture is already unloaded
            UnloadTexture(sprite_components[i].texture);
        }
    }
}
