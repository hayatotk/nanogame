#include "Render.hpp"

void draw_text(SDL_Renderer* renderer, TTF_Font* font, int x, int y, const char* message) {
    SDL_Color color = {255, 0, 0, 255};

    SDL_Surface* surface = TTF_RenderText_Solid(font, message, color);
    if (!surface) {
        return;
    }

    const char* prev_quality = SDL_GetHint(SDL_HINT_RENDER_SCALE_QUALITY);
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "0");

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

    if (prev_quality) {
        SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, prev_quality);
    } else {
        SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
    }

    if (!texture) {
        SDL_FreeSurface(surface);
        return;
    }

    SDL_Rect dst = {x, y, surface->w, surface->h};
    SDL_RenderCopy(renderer, texture, nullptr, &dst);

    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}
