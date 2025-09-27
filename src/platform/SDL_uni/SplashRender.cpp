#include "SplashRender.hpp"

void render_splash_sdl(SDL_Renderer* renderer, const Splash& splash) {
    float alpha = splash.getAlpha();
    Uint8 a = static_cast<Uint8>(alpha * 255);

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, a);
    SDL_Rect rect = {200, 200, 400, 200};
    SDL_RenderFillRect(renderer, &rect);

    SDL_RenderPresent(renderer);
}
