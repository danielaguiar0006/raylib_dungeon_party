#pragma once

#include <string.h>
#include "../utils/defines.h"
#include "../core/logger.h"

typedef struct tag_component {
    // Went for char array instead of string to avoid dynamic memory allocation
    char tag[64];  // Max length of a tag for the tag component
} tag_component;

/**
 * @brief Sets the tag of a tag_component.
 * @param component The tag_component to set the tag for.
 * @param tag The tag to set.
 */
void set_tag(tag_component* component, const char* tag);

/**
 * @brief Retrieves the tag from a tag_component.
 * @param component The tag_component to retrieve the tag from.
 * @return The tag string.
 */

const char* get_tag(const tag_component* component);

// TODO: Maybe add overloads for set_tag and get_tag with entity parameter, instead of passing the component directly
