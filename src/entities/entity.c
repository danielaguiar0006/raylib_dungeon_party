#include "entity.h"

// Array to track which components an entity has using bits
u32 entity_component_masks[GLOBAL_MAX_ENTITIES] = { 0 };
// total number of entities
static u32 entity_count = 0;

entity create_entity(void) {
    if (entity_count < GLOBAL_MAX_ENTITIES) {
        for (u32 i = 1; i < GLOBAL_MAX_ENTITIES; i++) {
            if (entity_component_masks[i] == COMPONENT_NONE) {
                entity_component_masks[i] = COMPONENT_ACTIVE;
                active_components[i].active = TRUE;
                entity_count++;
                return i;
            }
        }
    }
    KERROR("Unable to create entity: No more entities slots available, consider increasing MAX_ENTITIES.");
    return INVALID_ENTITY; // 0 is reserved for invalid entities
}

void destroy_entity(entity ent) {
    if (!is_valid_entity(ent)) {
        KWARN("Invalid entity: %d, cannot delete.", ent);
        return;
    }

    // Reset the data in each component array
    memset(&active_components[ent], 0, sizeof(active_component));
    memset(&tag_components[ent], 0, sizeof(tag_component));
    memset(&transform_components[ent], 0, sizeof(transform_component));
    memset(&sprite_components[ent], 0, sizeof(sprite_component));
    memset(&movement_components[ent], 0, sizeof(movement_component));
    memset(&collider_components[ent], 0, sizeof(collider_component));

    // Remove enitity from component masks array and decrement entity count
    entity_component_masks[ent] = COMPONENT_NONE;
    entity_count--;
}

b8 is_valid_entity(entity ent) {
    // INVALID_ENTITY is 0, so 0 is reserved for invalid entities
    // Logs warnings are defined in specific implementations
    return ent < GLOBAL_MAX_ENTITIES && entity_component_masks[ent] != COMPONENT_NONE && ent != INVALID_ENTITY;
}

u32 get_entity_count(void) {
    return entity_count;
}

entity get_entity_by_index(u32 index) {
    if (is_valid_entity(index)) {
        return index;
    }
    KWARN("Invalid entity index: %d", index);
    return INVALID_ENTITY;
}
