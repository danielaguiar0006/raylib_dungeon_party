#pragma once

#include "../utils/defines.h"
#include "entity.h"

/**
 * @brief Creates a player entity.
 * @return The created player entity.
 *         Returns INVALID_ENTITY (0) if an error occurs.
 */
entity create_player_entity(void);

/**
 * @brief Adds the necessary components to the player entity.
 * @param player The player entity to add components to.
 */
void add_player_components(entity player);
//TODO: void destroy_player_entity(entity player);

/**
 * @brief Retrieves the speed of the player.
 * @return The speed of the player as a floating-point value.
 */
f32 get_player_speed(void);

/**
 * @brief Sets the speed of the player.
 * @param speed The speed value to set for the player.
 */
void set_player_speed(f32 speed);
