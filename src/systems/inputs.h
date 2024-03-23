#pragma once

#include "../components/component_manager.h"
#include "../utils/defines.h"
#include "../utils/globals.h"


Vector2 handle_inputs();
/*
void PlayerInputSystem() {
    // Get the player entity
    entity player = ...;

    // Get the MovementComponent of the player
    MovementComponent* movement = get_component(player, COMPONENT_MOVEMENT);
    if (movement == NULL) {
        // Handle error: player does not have a MovementComponent
        return;
    }

    // Read input and update the MovementComponent
    if (IsKeyDown(KEY_W) || IsGamepadButtonDown(GAMEPAD_PLAYER1, GAMEPAD_BUTTON_LEFT_FACE_UP)) {
        movement->dy = -1;
    }
    else if (IsKeyDown(KEY_S) || IsGamepadButtonDown(GAMEPAD_PLAYER1, GAMEPAD_BUTTON_LEFT_FACE_DOWN)) {
        movement->dy = 1;
    }
    else {
        movement->dy = 0;
    }

    if (IsKeyDown(KEY_A) || IsGamepadButtonDown(GAMEPAD_PLAYER1, GAMEPAD_BUTTON_LEFT_FACE_LEFT)) {
        movement->dx = -1;
    }
    else if (IsKeyDown(KEY_D) || IsGamepadButtonDown(GAMEPAD_PLAYER1, GAMEPAD_BUTTON_LEFT_FACE_RIGHT)) {
        movement->dx = 1;
    }
    else {
        movement->dx = 0;
    }
}
*/

//TODO:
/*
If you find it odd for handle_inputs() to return a Vector2 for movement, you could consider using a global or singleton InputState structure that gets updated by handle_inputs(). This structure could hold all the current input states, including movement, actions, menu navigation, etc.

Here's an example of how you could do this:
// In inputs.h

#pragma once

#include "../components/component_manager.h"
#include "../utils/defines.h"
#include "../utils/globals.h"

struct InputState {
    Vector2 movement;
    bool isJumping;
    bool isAttacking;
    // Add other input states as needed
};

extern InputState inputState;

void handle_inputs();

// In inputs.cpp

InputState inputState;

void handle_inputs() {
    // Handle movement input
    inputState.movement = handle_movement_input();

    // Handle action input
    handle_action_input();

    // Handle menu input
    handle_menu_input();

    // Handle pause input
    handle_pause_input();

    // Handle camera input
    handle_camera_input();
}
In this code, handle_inputs() updates a global InputState structure instead of returning a value. Each specific input handling function updates the relevant part of the InputState. Other parts of your code can then read the InputState to get the current input. This approach keeps all the input handling code in one place, while still allowing other parts of your code to access the input state.
*/


/*
A singleton is a design pattern that restricts a class to a single instance. This means that no matter how many times you request an instance of the class, you always get the same one. This is useful when you need to coordinate actions across a system, and a single point of control or communication is required.

In C, you can't restrict the creation of another instance of a struct like you can in object-oriented languages with private constructors. However, you can create a single global instance and establish a convention that only this instance should be used.

Here's an example of how you could create a singleton-like structure in C:

// In InputState.h

typedef struct {
    Vector2 movement;
    bool isJumping;
    bool isAttacking;
    // Add other input states as needed
} InputState;

//extern InputState* get_input_state(); "extern" is not needed here
InputState* get_input_state();

// In InputState.c

static InputState inputState;

InputState* get_input_state() {
    return &inputState;
}
```

In this code, `get_input_state` returns a pointer to the single `InputState` instance. Other parts of your code should use `get_input_state` to access the `InputState`, rather than creating their own `InputState` instances.

Remember, this doesn't prevent someone from creating another `InputState` instance, but it establishes a convention that the `InputState` returned by `get_input_state` is the one that should be used. This is about as close as you can get to a true singleton in C.
*/
