#pragma once

#include <string.h>
#include "../utils/defines.h"

typedef struct tag_component {
    // Went for char array instead of string to avoid dynamic memory allocation
    char tag[64];  // Max length of a tag for the tag component
} tag_component;

void set_tag(tag_component* component, const char* tag);
