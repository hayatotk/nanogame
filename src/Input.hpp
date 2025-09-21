#pragma once
#include <SDL2/SDL.h>
#include "Config.hpp"

inline bool is_pressed(const Uint8* state, int key) {
    return state[key];
}
