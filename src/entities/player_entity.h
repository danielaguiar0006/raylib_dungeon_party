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
