#pragma once
#include <SDL2/SDL.h>

struct Player {
    float x, y;
    float vx, vy;
    int crouch;
    int run;
    int jumps;
    int prev_jump;
    int on_ground;
};

Player init_player(float start_x, float start_y);
void handle_input(Player& player, const Uint8* keys);
void update_physics(Player& player);
void render_player(const Player& player, SDL_Renderer* renderer, bool show_hitboxes);
