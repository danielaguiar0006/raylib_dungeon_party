#include "update_entity_transforms.h"

void update_entity_transforms(void) {  // ! Inactive entities are still updated
    for (u32 i = 0; i < GLOBAL_MAX_ENTITIES; i++) {
        if (has_component(i, COMPONENT_TRANSFORM)) {
            // Update grid position based on the current x and y in pixels
            transform_components[i].grid_x = transform_components[i].x / (TILE_SIZE_PX * TILE_SCALE_FACTOR);
            transform_components[i].grid_y = transform_components[i].y / (TILE_SIZE_PX * TILE_SCALE_FACTOR);

            if (has_component(i, COMPONENT_MOVEMENT)) {
                // Get the entity's movement component
                movement_component* movement = get_component(i, COMPONENT_MOVEMENT);

                // Update the entity's x and y position based on its velocity
                transform_components[i].x += movement->dx;
                transform_components[i].y += movement->dy;
            }

            // Update sprite transforms
            if (has_component(i, COMPONENT_SPRITE)) {  // COMPONENT_TRANSFORM && COMPONENT_SPRITE
                sprite_components[i].source_rectangle.width = transform_components[i].width;
                sprite_components[i].source_rectangle.height = transform_components[i].height;
            }
        }
    }
}
