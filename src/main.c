// DEBUG with cmake debug

#include "raylib.h"

#include "utils/defines.h"
#include "core/globals.h"
#include "entities/entity.h"
#include "components/component_manager.h"
#include "systems/systems.h"
#include "core/logger.h"
#include "utils/grid.h"
// TODO: create entity handler or something like that to handle entity creation and destruction
#include "entities/player_entity.h"

// Local Variables Definition (local to this module)
static Camera2D camera = { 0 };
static entity player;
static transform_component* player_transform;
static sprite_component* player_sprite;
static tag_component* player_tag;
static movement_component* player_movement;

// Local Functions Declaration
static void UpdateDrawFrame(void);  // Update and draw one frame
static void setup_window(void);     // Setup raylib window

// Main entry point
int main(void) {
    // Initialization
    setup_window();  // ! Must be called before any other initialization
    init_component_manager();
    init_systems();
    init_grid();

    player = create_player_entity();
    player_transform = (transform_component*)get_component(player, COMPONENT_TRANSFORM);
    player_sprite = (sprite_component*)get_component(player, COMPONENT_SPRITE);
    player_tag = (tag_component*)get_component(player, COMPONENT_TAG);
    player_movement = (movement_component*)get_component(player, COMPONENT_MOVEMENT);

    // TODO: move init_player_actions() to player_entity.c, maybe?
    init_player_actions(); // ! Must be called after player entity is created

    camera.target = (Vector2){ 0.0f, 0.0f };
    camera.offset = (Vector2){ 0.0f, 0.0f };  // Top-left corner = (0, 0)
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;

    SetTargetFPS(200);  // Set our game's frames-per-second

    // Main game loop
    while (!WindowShouldClose()) {  // Detect window close button or ESC key
        UpdateDrawFrame();
    }

    // De-Initialization
    destroy_systems();
    destroy_grid();
    CloseWindow();  // Close window and OpenGL context
    return 0;
}

// Update and draw game frame
static void UpdateDrawFrame(void) {
    // Update
    f32 delta_time = GetFrameTime();
    update_systems(delta_time);
    update_grid();

    // --- DEBUG -----------------------------------
    printf("\nx: %f", player_movement->dx);
    printf("\ny: %f", player_movement->dy);
    printf("\nspeed: %f", player_movement->current_speed);

    if (IsKeyPressed(KEY_E)) {
        entity ent = create_entity();
        //KDEBUG(TextFormat("created entity %d", ent));
        KDEBUG("Created entity: %d", ent);
        //add_component(ent, COMPONENT_POSITION);
    }

    if (IsKeyPressed(KEY_Q)) {
        active_components[player].active = !active_components[player].active;
    }
    if (IsKeyPressed(KEY_Z)) {
        // All other components must be removed before removing the "active" component
        remove_component(player, COMPONENT_ACTIVE);
    }
    if (IsKeyPressed(KEY_X)) {
        remove_component(player, COMPONENT_TRANSFORM);
    }
    if (IsKeyPressed(KEY_C)) {
        remove_component(player, COMPONENT_SPRITE);
    }
    if (IsKeyPressed(KEY_V)) {
        remove_component(player, COMPONENT_TAG);
    }
    // ---------------------------------------------


    // Draw
    BeginDrawing();

    ClearBackground(RAYWHITE);

    BeginMode2D(camera);

    draw_grid();
    draw_sprites();
    // DrawRectangleRec(player_sprite->source_rectangle, RED);  // Debug
    // debug midpoint of player
    //DrawCircle(get_transform_midpoint(player_transform).x, get_transform_midpoint(player_transform).y, 5, RED);

    EndMode2D();

    DrawText(TextFormat("entity count: %i", get_entity_count()), 10, 30, 20, DARKGRAY);
    DrawText(TextFormat("player.x = : %f, .y = %f", transform_components[player].x, transform_components[player].y), 10, 60, 20, DARKGRAY);
    DrawText(TextFormat("player.grid_x = : %f, .grid_y = %f", transform_components[player].grid_x, transform_components[player].grid_y), 10, 90, 20, DARKGRAY);
    DrawText(TextFormat("player.active = %i", active_components[player].active), 10, 120, 20, DARKGRAY);
    DrawText(TextFormat("player.tag = %s", tag_components[player].tag), 10, 150, 20, DARKGRAY);
    DrawFPS(10, 10);

    EndDrawing();
}

void setup_window(void) {
    InitWindow(window_width, window_height, "Dungeon Party");
    //SetWindowState(FLAG_VSYNC_HINT);  // VSYNC ON
}
