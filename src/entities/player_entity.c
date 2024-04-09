#include "player_entity.h"

static f32 player_speed = 200.0f;

entity create_player_entity(void) {
    entity player = create_entity();  // ! Will return INVALID_ENTITY (0) if error
    if (player == INVALID_ENTITY) {
        KERROR("Unable to create player entity.");
        return INVALID_ENTITY;
    }
    add_player_components(player);
    return player;
}

void add_player_components(entity player) {
    // Add components to player entity
    add_component(player, COMPONENT_TRANSFORM);
    add_component(player, COMPONENT_SPRITE);
    add_component(player, COMPONENT_TAG);

    // Set Player's sprite component
    sprite_components[player].texture = LoadTexture("../../assets/textures/player.png");

    // Set player's tag to "player"
    // HACK: Getting tag component first to set the tag
    tag_component* player_tag;
    player_tag = (tag_component*)get_component(player, COMPONENT_TAG);
    set_tag(player_tag, "player");
}

f32 get_player_speed(void) {
    return player_speed;
}

void set_player_speed(f32 speed) {
    player_speed = speed;
}

// TODO: add more setter functions for player entity stats
