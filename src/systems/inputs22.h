
#pragma once

#include "../components/component_manager.h"
#include "../utils/defines.h"
#include "../utils/globals.h"


Vector2 handle_inputs();

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

/*
The `InputState` struct is a way to encapsulate all the possible inputs in your game into a single data structure. How you use it depends on the specifics of your game.

If you have a `is_attacking` field in your `InputState`, you could set it to `true` when the player clicks the mouse button, and then in your game logic, you would check the `is_attacking` field to determine if the player is trying to attack.

Similarly, if you have a `menu_select_ok` field, you could set it to `true` when the player presses the Enter key (or any other key you want to use to confirm menu selections), and then in your menu logic, you would check the `menu_select_ok` field to determine if the player is trying to confirm a menu selection.

Here's an example of how you might handle mouse clicks and menu selections:

```c
void handle_inputs(void) {
    // Handle movement input
    input_state.movement_delta = handle_movement_input();

    // Handle mouse clicks
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        input_state.is_attacking = true;
    } else {
        input_state.is_attacking = false;
    }

    // Handle menu selections
    if (IsKeyPressed(KEY_ENTER)) {
        input_state.menu_select_ok = true;
    } else {
        input_state.menu_select_ok = false;
    }
}
```

In your game logic, you would then check these fields to determine what action to take. For example:

```c
void update_game(void) {
    InputState* input_state = get_input_state();

    if (input_state->is_attacking) {
        // Perform attack
    }

    if (input_state->menu_select_ok) {
        // Confirm menu selection
    }

    // Handle movement
    Vector2 movement_delta = input_state->movement_delta;
    // Move player character based on movement_delta
}
```

This is just a basic example. The specifics will depend on how your game is structured and what kind of input you want to handle.
*/

/*
Yes, you're correct. If both `is_attacking` and `menu_select_ok` are triggered by the same input (for example, a mouse click), they would both be set to `true` when that input is received.

In your game logic, you would then check the current game state or context to determine which action to take. For example, if the game is in combat mode, you might check the `is_attacking` field and ignore the `menu_select_ok` field. If the game is in menu mode, you might do the opposite.

Here's an example:

```c
void handle_inputs(void) {
    // Handle movement input
    input_state.movement_delta = handle_movement_input();

    // Handle mouse clicks
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        input_state.is_attacking = true;
        input_state.menu_select_ok = true;
    } else {
        input_state.is_attacking = false;
        input_state.menu_select_ok = false;
    }
}

void update_game(void) {
    InputState* input_state = get_input_state();

    if (game_state == GAME_STATE_COMBAT) {
        if (input_state->is_attacking) {
            // Perform attack
        }
    } else if (game_state == GAME_STATE_MENU) {
        if (input_state->menu_select_ok) {
            // Confirm menu selection
        }
    }

    // Handle movement
    Vector2 movement_delta = input_state->movement_delta;
    // Move player character based on movement_delta
}
```

In this example, `game_state` is a variable that represents the current state of the game. `GAME_STATE_COMBAT` and `GAME_STATE_MENU` are constants that represent different game states. You would need to define these in your code.
*/
