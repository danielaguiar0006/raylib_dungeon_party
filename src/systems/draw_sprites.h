#pragma once

#include "../components/component_manager.h"
#include "../utils/defines.h"
#include "../core/globals.h"

/**
 * @brief Draws all the sprites in the game.
 * This function iterates through all the entities in the game and checks if they have the required components
 * (Active, sprite, and transform). If an entity has all the required components, its sprite is drawn on the screen.
 */
void draw_sprites(void);

/**
 * @brief Unloads all textures from sprite components.
 */
void unload_sprites(void);
