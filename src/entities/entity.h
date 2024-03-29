#pragma once

#include "../utils/defines.h"
#include "../utils/globals.h"
#include "../components/component_manager.h"

typedef u32 entity;

extern u32 entity_component_masks[GLOBAL_MAX_ENTITIES];

/**
 * @brief Creates a new entity
 * @return The newly created entity. or 0 if global_max_entities is reached.
 */
entity create_entity(void);

/**
 * @brief Destroys an entity.
 * This function destroys the given entity by freeing any allocated memory and
 * performing any necessary cleanup operations.
 * @param ent The entity to be destroyed.
 */
void destroy_entity(entity ent);

/**
 * @brief Checks if the given entity is valid.
 * @param ent The entity to check.
 * @return Returns true if the entity is valid, false otherwise.
 */
b8 is_valid_entity(entity ent);

/**
 * @brief Returns the count of entities.
 * @return The count of entities.
 */
u32 get_entity_count(void);

/**
 * @brief Retrieves an entity by its index.
 * @param index The index of the entity to retrieve.
 * @return The entity with the specified index, or 0 if the index is invalid.
 */
entity get_entity_by_index(u32 index);
