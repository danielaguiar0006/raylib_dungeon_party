#include "transform_component.h"

Vector2 get_transform_midpoint(transform_component* component) {
    if (component == NULL) {
        KERROR("Unable to get transform midpoint: Component is NULL");
        return (Vector2) { 0, 0 };  // If component is NULL, return the origin
    }
    return (Vector2) {
        component->x + ((component->width * TILE_SCALE_FACTOR) / 2.0f),
            component->y + ((component->height * TILE_SCALE_FACTOR) / 2.0f)
    };
}

void set_transform_position_pixels(transform_component* component, f32 x, f32 y) {
    if (component == NULL) {
        KERROR("Unable to set position: Component is NULL");
        return;
    }
    component->x = x;
    component->y = y;
}

void set_transform_position_grid(transform_component* component, f32 x, f32 y) {
    if (component == NULL) {
        KERROR("Unable to set position: Component is NULL");
        return;
    }
    component->grid_x = x;
    component->grid_y = y;
    component->x = x * TILE_SIZE_PX * TILE_SCALE_FACTOR;
    component->y = y * TILE_SIZE_PX * TILE_SCALE_FACTOR;
}
