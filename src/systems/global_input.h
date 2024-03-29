#pragma once

#include "../components/component_manager.h"
#include "../utils/defines.h"
#include "../utils/globals.h"

typedef struct ActionInput {
    Vector2 movement_delta;
    b8 is_jumping;
    b8 is_attacking;
} ActionInput;

typedef struct MenuInput {
    b8 is_up;
    b8 is_down;
    b8 is_left;
    b8 is_right;
    b8 is_select;
    b8 is_back;
} MenuInput;

typedef struct InputState {
    MenuInput menu_input;
    ActionInput action_input;
    // TODO: Add other input states as needed
} InputState;

void handle_global_inputs(void);
InputState* get_input_state(void);
