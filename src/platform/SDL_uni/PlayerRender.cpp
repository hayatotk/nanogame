#include "../../core/Player.hpp"
#include "../../Config.hpp"
#include <SDL2/SDL.h>

void render_player_sdl(const Player& player, SDL_Renderer* renderer, bool show_hitboxes) {
    SDL_Rect rect = {
        (int)player.x,
        (int)player.y + (player.crouch ? 16 : 0),
        32,
        32 - (player.crouch ? 16 : 0)
    };

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, &rect);

    if (show_hitboxes) {
        SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
        SDL_RenderDrawRect(renderer, &rect);
    }
}
