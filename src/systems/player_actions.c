#include "player_actions.h"

// Prototypes
static void update_player_movement(f32 delta_time);
static entity find_player(void);

// Static globals
static entity player = INVALID_ENTITY;

void init_player_actions(void) {
    // Try to find the player entity
    player = find_player();

    // Check if the player entity exists
    if (player == INVALID_ENTITY) {
        KERROR("player entity not found");
    }
    else {
        KDEBUG("found player: %d", player);
    }
}

void update_player_actions(f32 delta_time) {
    update_player_movement(delta_time);
}

static void update_player_movement(f32 delta_time) {
    if (has_component(player, COMPONENT_TRANSFORM) && has_component(player, COMPONENT_ACTIVE)) {
        // Get the player's transform component
        transform_component* player_transform = get_component(player, COMPONENT_TRANSFORM);
        //Vector2* movement_delta = &get_input_state()->action_input.movement_delta;
        Vector2* movement_delta = &get_input_state()->action_input.movement_delta;

        // TODO: move() function or something

        if (active_components[player].active == TRUE) {
            // Move the player entity
            //TODO: change 100.0f to player_speed or something
            player_transform->x += movement_delta->x * delta_time * get_player_speed();
            player_transform->y += movement_delta->y * delta_time * get_player_speed();
        }
    }
}

// Find the player entity
static entity find_player(void) {  // TODO: maybe move to entity.c or something?
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
