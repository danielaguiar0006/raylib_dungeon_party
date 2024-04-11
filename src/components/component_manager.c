#include "component_manager.h"

static const f32 DEFAULT_X = 0.0f;
static const f32 DEFAULT_Y = 0.0f;
static const f32 DEFAULT_SPEED_MULTIPLIER = 1.0f;
static const f32 DEFAULT_MAX_SPEED = 250.0f;
static const f32 DEFAULT_ACCELERATION = 750.0f;
static const f32 DEFAULT_DECELERATION = 3000.0f;

active_component active_components[GLOBAL_MAX_ENTITIES] = { 0 };
tag_component tag_components[GLOBAL_MAX_ENTITIES] = { 0 };
transform_component transform_components[GLOBAL_MAX_ENTITIES] = { 0 };
sprite_component sprite_components[GLOBAL_MAX_ENTITIES] = { 0 };
movement_component movement_components[GLOBAL_MAX_ENTITIES] = { 0 };
collider_component collider_components[GLOBAL_MAX_ENTITIES] = { 0 };

// TODO: not doing anything with this yet
void init_component_manager(void) {
    // initialize component storage, if needed
}

b8 has_component(entity ent, component_flags component_flag) {
    if (!is_valid_entity(ent)) {
        // FIXME: causes too many warnings
        //KWARN("Unable to check for component: Invalid entity: %d", ent);
        return FALSE;
    }
    return (entity_component_masks[ent] & component_flag) == component_flag;
}

// TODO implement a way to add/remove multiple components at once
void add_component(entity ent, component_flags component) {
    if (!is_valid_entity(ent)) {
        KERROR("Unable to add component: Invalid entity: %d", ent);
        return;
    }
    if (component == COMPONENT_NONE) {
        KWARN("Unable to add component \"COMPONENT_NONE\" to %d, instead use remove_component() or destroy_entity() instead.", ent);
        return;
    }
    if (has_component(ent, component)) {
        KWARN("Unable to add component: Entity %d already has component %d.", ent, component);
        return;
    }

    switch (component) {    // Default values for each component
    case COMPONENT_ACTIVE:  // Active by default when create_entity() is called
        active_components[ent].active = TRUE;
        break;
    case COMPONENT_TAG:  // Active by default when create_entity() is called
        //strcpy(tag_components[ent].tag, "");
        // ! Using strncpy() for safety, but it's not necessary here, and might introduce weirdness
        strncpy(tag_components[ent].tag, "", sizeof(tag_components[ent].tag));  // Safe copy
        tag_components[ent].tag[sizeof(tag_components[ent].tag) - 1] = '\0';    // Ensure null termination
        break;
    case COMPONENT_TRANSFORM:
        transform_components[ent].x = DEFAULT_X;
        transform_components[ent].y = DEFAULT_Y;
        transform_components[ent].grid_x = DEFAULT_X;
        transform_components[ent].grid_y = DEFAULT_Y;
        transform_components[ent].width = TILE_SIZE_PX;
        transform_components[ent].height = TILE_SIZE_PX;
        transform_components[ent].rotation = 0.0f;            // Default rotation (radians)
        transform_components[ent].scale = TILE_SCALE_FACTOR;  // Default scale
        break;
    case COMPONENT_MOVEMENT:
        movement_components[ent].current_speed = 0.0f;
        movement_components[ent].speed_multiplier = DEFAULT_SPEED_MULTIPLIER;
        movement_components[ent].max_speed = DEFAULT_MAX_SPEED;
        movement_components[ent].acceleration = DEFAULT_ACCELERATION;
        movement_components[ent].deceleration = DEFAULT_DECELERATION;
        movement_components[ent].dx = 0.0f;
        movement_components[ent].dy = 0.0f;
        movement_components[ent].last_dx = 0.0f;
        movement_components[ent].last_dy = 0.0f;
        break;
    case COMPONENT_SPRITE:  // NOTE: Textures MUST be loaded after Window Initialization
        // FIXME: LoadTexture() is called for every new sprite component added on the same texture
        // TODO: Implement some sort of texture manager to prevent this
        // HACK: texture path is hardcoded for now, try (assets/textures/debug_empty.png) if it fails
        Texture2D texture = LoadTexture("../../assets/textures/debug_empty.png");
        // set texture filter and wrap mode before setting the texture
        SetTextureFilter(texture, TEXTURE_FILTER_POINT);
        SetTextureWrap(texture, TEXTURE_WRAP_CLAMP);
        sprite_components[ent].texture = texture;
        sprite_components[ent].source_rectangle = (Rectangle){  // FIXME: not working, so not used
            DEFAULT_X,
            DEFAULT_Y,
            TILE_SIZE_PX,
            TILE_SIZE_PX };
        sprite_components[ent].tint = WHITE;
        break;
    case COMPONENT_COLLIDER:
        collider_components[ent].x = DEFAULT_X;
        collider_components[ent].y = DEFAULT_Y;
        collider_components[ent].width = TILE_SIZE_PX;
        collider_components[ent].height = TILE_SIZE_PX;
        collider_components[ent].scale = TILE_SCALE_FACTOR;
        collider_components[ent].is_colliding = FALSE;
        break;
    default:
        KERROR("Unable add component: Invalid component: %d", component);
        return;
    }
    // Add component to the entity's mask
    entity_component_masks[ent] |= component;
    KDEBUG("Added component %d to entity %d", component, ent);
}

void remove_component(entity ent, component_flags component) {
    if (!is_valid_entity(ent)) {
        KERROR("Unable remove component: Invalid entity: %d", ent);
        return;
    }
    if (component == COMPONENT_NONE) {
        KWARN("Unable to remove component: \"COMPONENT_NONE\" from %d, instead use add_component() or create_entity() instead.", ent);
        return;
    }
    if (!has_component(ent, component)) {
        KWARN("Unable to remove component: Entity %d does not have component %d.", ent, component);
        return;
    }

    switch (component) {
    case COMPONENT_ACTIVE:
        if (entity_component_masks[ent] != COMPONENT_ACTIVE) {  // If there are other components
            // * Get rid of other components first, then remove active component or call destroy_entity()
            KERROR("Unable remove active component from entity %d, it is required for other components.", ent);
            return;
        }

        // Completely destroy the entity (reset bitmask and decrement entity count)
        destroy_entity(ent);
        break;
    case COMPONENT_TAG:
        memset(&tag_components[ent], 0, sizeof(tag_component));
        break;
    case COMPONENT_TRANSFORM:
        memset(&transform_components[ent], 0, sizeof(transform_component));
        break;
    case COMPONENT_MOVEMENT:
        memset(&movement_components[ent], 0, sizeof(movement_component));
        break;
    case COMPONENT_SPRITE:
        UnloadTexture(sprite_components[ent].texture);  // Unload the texture from memory
        memset(&sprite_components[ent], 0, sizeof(sprite_component));
        break;
    case COMPONENT_COLLIDER:
        memset(&collider_components[ent], 0, sizeof(collider_component));
        break;
    default:
        KERROR("Unable Remove Component: Invalid component: %d", component);
        return;
    }
    // remove component to the entity's mask
    entity_component_masks[ent] &= ~component;
    KDEBUG("Removed component %d from entity %d", component, ent);
}

void* get_component(entity ent, component_flags component_flag) {
    if (!has_component(ent, component_flag)) {
        KERROR("Unable get component: Entity %d does not have component %d", ent, component_flag);
        return NULL;
    }
    else {
        switch (component_flag) {
        case COMPONENT_ACTIVE:
            return &active_components[ent];
        case COMPONENT_TAG:
            return &tag_components[ent];
        case COMPONENT_TRANSFORM:
            return &transform_components[ent];
        case COMPONENT_MOVEMENT:
            return &movement_components[ent];
        case COMPONENT_SPRITE:
            return &sprite_components[ent];
        case COMPONENT_COLLIDER:
            return &collider_components[ent];
        default:
            KERROR("Unable get component: Invalid component: %d", component_flag);
            return NULL;
        }
    }
}
