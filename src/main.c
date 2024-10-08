// * DEBUG with cmake debug for breakpoints to work

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
    if (IsKeyPressed(KEY_E)) {
        entity ent = create_entity();
        //KDEBUG(TextFormat("created entity %d", ent));
        KDEBUG("Created entity: %d", ent);
        add_component(ent, COMPONENT_TRANSFORM);
        add_component(ent, COMPONENT_SPRITE);

        set_transform_position_grid(&transform_components[ent], 12, 7);
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
    if (IsKeyPressed(KEY_B)) {
        remove_component(player, COMPONENT_MOVEMENT);
    }

    if (IsKeyPressed(KEY_UP)) {
        player_movement->speed_multiplier += 0.1f;
    }
    else if (IsKeyPressed(KEY_DOWN)) {
        player_movement->speed_multiplier -= 0.1f;
    }
    // ---------------------------------------------


    // Draw
    BeginDrawing();

    ClearBackground(RAYWHITE);

    BeginMode2D(camera);

    draw_grid();
    draw_sprites();

    EndMode2D();

    DrawFPS(10, 10);
    DrawText(TextFormat("entity count: %i", get_entity_count()), 10, 30, 20, DARKGRAY);
    DrawText(TextFormat("player.x = : %f, .y = %f", transform_components[player].x, transform_components[player].y), 10, 60, 20, DARKGRAY);
    DrawText(TextFormat("player.grid_x = : %f, .grid_y = %f", transform_components[player].grid_x, transform_components[player].grid_y), 10, 90, 20, DARKGRAY);
    DrawText(TextFormat("player.active = %i", active_components[player].active), 10, 120, 20, DARKGRAY);
    DrawText(TextFormat("player.tag = %s", tag_components[player].tag), 10, 150, 20, DARKGRAY);
    DrawText(TextFormat("player.dx = %f : player.dy = %f", movement_components[player].dx, movement_components[player].dy), 10, 180, 20, DARKGRAY);
    DrawText(TextFormat("player.current_speed = %f", movement_components[player].current_speed), 10, 210, 20, DARKGRAY);
    DrawText(TextFormat("player.speed_multiplier = %f", movement_components[player].speed_multiplier), 10, 240, 20, DARKGRAY);

    EndDrawing();
}

void setup_window(void) {
    InitWindow(window_width, window_height, "Dungeon Party");
    //SetWindowState(FLAG_VSYNC_HINT);  // VSYNC ON
}
