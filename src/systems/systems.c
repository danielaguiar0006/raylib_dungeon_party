#include "systems.h"

void init_systems(void) {
}

void update_systems(f32 delta_time) {
    // Update all systems:
    handle_global_inputs();
    update_player_actions(delta_time);
    update_entity_transforms();
}

void destroy_systems(void) {
    // Destroy all systems:
    unload_sprites();
}
