#include "tag_component.h"

void set_tag(tag_component* component, const char* tag) {
    if (component == NULL || tag == NULL) {
        KERROR("Unable to set tag: Component or tag is NULL");
        return;
    }

    size_t tag_length = strlen(tag);
    if (tag_length >= sizeof(component->tag)) {
        KERROR("Unable to set tag: Tag is too long: %s", tag);
        return;
    }

    strncpy(component->tag, tag, sizeof(component->tag));  // Safe copy
    component->tag[sizeof(component->tag) - 1] = '\0';     // Ensure null termination
}

const char* get_tag(const tag_component* component) {
    if (component == NULL) {
        KERROR("Unable to get tag: Component is NULL");
        return NULL;
    }

    return component->tag;
}
