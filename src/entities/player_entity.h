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
 * @brief Retrieves the player entity.
 * @return The player entity.
 */
entity get_player(void);

//TODO: void destroy_player_entity(entity player);
