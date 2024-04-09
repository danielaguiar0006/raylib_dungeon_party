#pragma once

#include "../utils/defines.h"
#include "../core/globals.h"
#include "../entities/entity.h"
#include "../core/logger.h"

// Components
#include "active_component.h"
#include "tag_component.h"
#include "transform_component.h"
#include "sprite_component.h"
#include "velocity_component.h"

// Constants
extern const f32 DEFAULT_X;
extern const f32 DEFAULT_Y;

// Component arrays, indexed by entity
extern active_component active_components[GLOBAL_MAX_ENTITIES];
extern tag_component tag_components[GLOBAL_MAX_ENTITIES];
extern transform_component transform_components[GLOBAL_MAX_ENTITIES];
extern sprite_component sprite_components[GLOBAL_MAX_ENTITIES];
extern velocity_component velocity_components[GLOBAL_MAX_ENTITIES];

void init_component_manager(void);

/**
 * @brief Checks if an entity has a specific component.
 * @param ent The entity to check.
 * @param component_flag The component flag to check for.
 * @return Returns true if the entity has the specified component, false otherwise.
 */
b8 has_component(entity ent, component_flags component_flag);

/**
 * @brief Adds a component to an entity with default values.
 * @param ent The entity to add the component to.
 * @param component The component to add.
 */
void add_component(entity ent, component_flags component);

/**
 * @brief Removes a component from an entity.
 * @param ent The entity from which to remove the component.
 * @param component The component to remove.
 */
void remove_component(entity ent, component_flags component);

/**
 * @brief Retrieves a pointer to the component of a given type attached to a specific entity.
 * This function returns a void pointer to the component specified by the component_flag parameter
 * that is attached to the entity specified by the ent parameter. The returned pointer can be cast
 * to the appropriate component type to access the component's data.
 * If the specified entity does not have a component of the specified type, the function returns NULL.
 *
 * @param ent The entity from which to retrieve the component.
 * @param component_flag The type of component to retrieve. This should be one of the values defined
 * in the component_flags enum.
 *
 * @return A void pointer to the requested component, or NULL if the entity does not have a component
 * of the requested type.
 */
void* get_component(entity ent, component_flags);
