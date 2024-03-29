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
