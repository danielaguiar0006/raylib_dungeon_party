#include "global_input.h"
#include "raymath.h"  // HACK: Including this in the header file cuases a redefinition error?!?

static b8 is_input_initialized = false;
static InputState input_state;  // Global input state | Singleton pattern

// Prototypes
static Vector2 handle_movement_input(void);

void handle_global_inputs(void) {
    // ? maybe memset the whole input_state?
    //memset(&input_state.action_input, 0, sizeof(ActionInput));  // Zero out the action input

    // pass by reference not necessary
    input_state.action_input.movement_delta = handle_movement_input();

    // TODO: handle other input types
    //handle_action_input(&input_state.action_input);
    //handle_menu_input(&input_state.menu_input);
    //handle_gui_input(&input_state.gui_input);
    //handle_camera_input(&input_state.camera_input);
    //handle_pause_input(&input_state.pause_input);
}

InputState* get_input_state(void) {  // Singleton pattern
    if (!is_input_initialized) {
        // Initialize input state here
        input_state = (InputState){ 0 };  // Zero out the input state
        is_input_initialized = true;
    }
    return &input_state;
}

static Vector2 handle_movement_input(void) {
    Vector2 movement_delta = { 0.0f, 0.0f };

    if (IsKeyDown(KEY_W)) {  // Up
        movement_delta.y -= 1.0f;
    }
    if (IsKeyDown(KEY_S)) {  // Down
        movement_delta.y += 1.0f;
    }
    if (IsKeyDown(KEY_A)) {  // Left
        movement_delta.x -= 1.0f;
    }
    if (IsKeyDown(KEY_D)) {  // Right
        movement_delta.x += 1.0f;
    }

    // TODO Test and enable controller support
/*     if (IsGamepadAvailable(GAMEPAD_PLAYER1)) {
        if (IsGamepadButtonPressed(GAMEPAD_PLAYER1, GAMEPAD_BUTTON_LEFT_FACE_UP)) {  // Up
            movement_delta.y -= 1.0f;
        }
        if (IsGamepadButtonPressed(GAMEPAD_PLAYER1, GAMEPAD_BUTTON_LEFT_FACE_DOWN)) {  // Down
            movement_delta.y += 1.0f;
        }
        if (IsGamepadButtonPressed(GAMEPAD_PLAYER1, GAMEPAD_BUTTON_LEFT_FACE_LEFT)) {  // Left
            movement_delta.x -= 1.0f;
        }
        if (IsGamepadButtonPressed(GAMEPAD_PLAYER1, GAMEPAD_BUTTON_LEFT_FACE_RIGHT)) {  // Right
            movement_delta.x += 1.0f;
        }

        // Analog stick input
        movement_delta.x += GetGamepadAxisMovement(GAMEPAD_PLAYER1, GAMEPAD_AXIS_LEFT_X);
        movement_delta.y += GetGamepadAxisMovement(GAMEPAD_PLAYER1, GAMEPAD_AXIS_LEFT_Y);
    } */

    // Check if the movement delta is non-zero (i.e. the player is moving)
    if (Vector2Length(movement_delta) > 0.0f) {
        movement_delta = Vector2Normalize(movement_delta);  // Normalize to prevent faster diagonal movement
        return movement_delta;
    }
    else {
        return (Vector2) { 0.0f, 0.0f };
    }
}
