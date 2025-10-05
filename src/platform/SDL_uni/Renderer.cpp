#include "Renderer.hpp"

SDLRenderer::SDLRenderer(SDL_Renderer* r, TTF_Font* f)
    : renderer(r), font(f) {}

void SDLRenderer::clear(uint8_t r, uint8_t g, uint8_t b) {
    SDL_SetRenderDrawColor(renderer, r, g, b, 255);
    SDL_RenderClear(renderer);
}

void SDLRenderer::drawRect(int x, int y, int w, int h,
                           uint8_t r, uint8_t g, uint8_t b) {
    SDL_SetRenderDrawColor(renderer, r, g, b, 255);
    SDL_Rect rect = {x, y, w, h};
    SDL_RenderFillRect(renderer, &rect);
}

void SDLRenderer::drawRectOutline(int x, int y, int w, int h,
                                  uint8_t r, uint8_t g, uint8_t b) {
    SDL_SetRenderDrawColor(renderer, r, g, b, 255);
    SDL_Rect rect = {x, y, w, h};
    SDL_RenderDrawRect(renderer, &rect);
}

void SDLRenderer::drawText(int x, int y, const std::string& msg,
                           uint8_t r, uint8_t g, uint8_t b) {
    if (!font) {
        SDL_Log("SDLRenderer::drawText called with null font");
        return;
    }

    SDL_Color color = {r, g, b, 255};
    SDL_Surface* surf = TTF_RenderText_Solid(font, msg.c_str(), color);
    if (!surf) {
        SDL_Log("TTF_RenderText_Solid failed: %s", TTF_GetError());
        return;
    }

    SDL_Texture* tex = SDL_CreateTextureFromSurface(renderer, surf);
    if (!tex) {
        SDL_Log("SDL_CreateTextureFromSurface failed: %s", SDL_GetError());
        SDL_FreeSurface(surf);
        return;
    }

    SDL_Rect dst = {x, y, surf->w, surf->h};
    SDL_RenderCopy(renderer, tex, nullptr, &dst);

    SDL_FreeSurface(surf);
    SDL_DestroyTexture(tex);
}

void SDLRenderer::present() {
    SDL_RenderPresent(renderer);
}
