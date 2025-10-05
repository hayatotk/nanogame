#pragma once
#include "InputState.hpp"

struct Player {
    float x, y;
    float vx, vy;
    int prev_jump;
    int jumps;
    int crouch;
    int run;
    int on_ground;
};

Player init_player(float start_x, float start_y);

void handle_input(Player& player, const InputState& input, float dt);

void update_physics(Player& player);
