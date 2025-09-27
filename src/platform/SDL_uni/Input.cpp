#include "Input.hpp"
#include "../../Config.hpp"
#include <SDL2/SDL.h>

static int key_left, key_right, key_jump, key_down, key_run, key_reset, key_fullscreen;

static void init_keymap() {
    key_left       = SDL_GetScancodeFromName(key_left_name.c_str());
    key_right      = SDL_GetScancodeFromName(key_right_name.c_str());
    key_jump       = SDL_GetScancodeFromName(key_jump_name.c_str());
    key_down       = SDL_GetScancodeFromName(key_down_name.c_str());
    key_run        = SDL_GetScancodeFromName(key_run_name.c_str());
    key_reset      = SDL_GetScancodeFromName(key_reset_name.c_str());
    key_fullscreen = SDL_GetScancodeFromName(key_fullscreen_name.c_str());
}

int get_fullscreen_scancode() {
    static bool initialized = false;
    if (!initialized) {
        init_keymap();
        initialized = true;
    }
    return key_fullscreen;
}


InputState get_input_from_sdl() {
    static bool initialized = false;
    if (!initialized) {
        init_keymap();
        initialized = true;
    }

    InputState state;
    const Uint8* keys = SDL_GetKeyboardState(nullptr);

    state.left   = keys[key_left];
    state.right  = keys[key_right];
    state.jump   = keys[key_jump];
    state.run    = keys[key_run];
    state.crouch = keys[key_down];
    state.reset  = keys[key_reset];

    return state;
}

