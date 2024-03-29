#include "player_actions.h"

// Find the player entity
static entity find_player() {
    for (u32 i = 0; i < GLOBAL_MAX_ENTITIES; i++) {
        // Check if the entity has the tag component
        if (has_component(i, COMPONENT_TAG)) {
            // Check if the entity has the "player" tag
            if (strcmp(tag_components[i].tag, "player") == 0) {
                return get_entity_by_index(i);
            }
        }
    }
    return INVALID_ENTITY;
}

void update_player_movement() {
    // Get the player entity
    entity player = find_player();  // TODO: should be moved to init system not update every frame
    KDEBUG("found player: %d", player);

    // Check if the player entity exists
    if (player == INVALID_ENTITY) {
        // TODO: log error
        return;
    }

    if (has_component(player, COMPONENT_TRANSFORM) && has_component(player, COMPONENT_ACTIVE)) {

        // Get the player's transform component
        transform_component* player_transform = get_component(player, COMPONENT_TRANSFORM);
        //Vector2* movement_delta = &get_input_state()->action_input.movement_delta;
        Vector2* movement_delta = &get_input_state()->action_input.movement_delta;

        // TODO: move() function or something

        if (active_components[player].active == TRUE) {
            // Move the player entity
            player_transform->x += movement_delta->x;
            player_transform->y += movement_delta->y;
        }
    }

    //TODO: make update_player_movement() static and call it from update_player_actions(). call update_player_actions() from main.c

/*     update_player_actions() {
        update_player_movement();
    } */
}
