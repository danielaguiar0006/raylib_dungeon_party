#include "tag_component.h"

void set_tag(tag_component* component, const char* tag) {
    if (component == NULL || tag == NULL) {
        //TODO: Handle error: null pointer
        return;
    }

    size_t tag_length = strlen(tag);
    if (tag_length >= sizeof(component->tag)) {
        //TODO: Handle error: tag is too long
        return;
    }

    strncpy(component->tag, tag, sizeof(component->tag));  // Safe copy
    component->tag[sizeof(component->tag) - 1] = '\0';     // Ensure null termination
}
