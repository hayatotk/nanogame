#pragma once
#include "../../core/Player.hpp"
#include <SDL2/SDL.h>

void render_player_sdl(const Player& player, SDL_Renderer* renderer, bool show_hitboxes);
