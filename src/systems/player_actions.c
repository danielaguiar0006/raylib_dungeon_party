#include "player_actions.h"

// Prototypes
static void update_player_movement(f32 delta_time);

// Static globals
static entity player = INVALID_ENTITY;
static movement_component* player_movement;

void init_player_actions(void) {
    // Get player entity
    player = get_player();

    // Check if the player entity exists
    if (player == INVALID_ENTITY) {
        KERROR("player entity not found");
    }
    else {
        KDEBUG("found player: %d", player);
        player_movement = get_component(player, COMPONENT_MOVEMENT);
    }
}

void update_player_actions(f32 delta_time) {
    update_player_movement(delta_time);
}

static void update_player_movement(f32 delta_time) {
    if (has_component(player, COMPONENT_TRANSFORM)
        && has_component(player, COMPONENT_ACTIVE)
        && has_component(player, COMPONENT_MOVEMENT)) {
        // Get the global input state
        Vector2* input_movement_delta = &get_input_state()->action_input.movement_delta;

        // Update the player's movement (input is already normalized between -1.0f and 1.0f)
        player_movement->dx = input_movement_delta->x * player_movement->speed_multiplier;
        player_movement->dy = input_movement_delta->y * player_movement->speed_multiplier;


        // Apply acceleration or deceleration and clamp the speed both max and min
        if (player_movement->dx != 0.0f || player_movement->dy != 0.0f) {
            // Acceleration
            player_movement->current_speed = fminf(player_movement->current_speed + player_movement->acceleration * delta_time,
                player_movement->max_speed);
        }
        else {
            // Deceleration
            player_movement->current_speed = fmaxf(0.0f, player_movement->current_speed - player_movement->deceleration * delta_time);
        }

        // Apply current_speed to dx and dy and multiply by delta_time
        player_movement->dx *= player_movement->current_speed * delta_time;
        player_movement->dy *= player_movement->current_speed * delta_time;

        // FIXME: Player slows down immediately when input is released
        // * Speed is being properly decelerated, but the transform component is
        // * using the dx and dy values directly, which are being set to 0 when the
        // * input is released. The player should continue moving in the last direction
        // * until the speed reaches 0.0f

        // * The player's transform is being updated in update_entity_transforms.c
    }
}
