#include "Splash.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <algorithm>

void run_splash(SDL_Renderer* renderer, TTF_Font* font) {
    Uint32 start_time = SDL_GetTicks();
    SDL_Event event;
    bool active = true;

    while (active) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                return;
            }
        }

        Uint32 elapsed = SDL_GetTicks() - start_time;
        float alpha = 1.0f;

        if (elapsed < 500) {
            alpha = static_cast<float>(elapsed) / 500.0f;          // fade in (0.5s)
        } else if (elapsed < 1500) {
            alpha = 1.0f;                                          // hold (1s)
        } else if (elapsed < 2500) {
            alpha = 1.0f - static_cast<float>(elapsed - 1500) / 1000.0f; // fade out (1s)
        } else {
            active = false;
        }

        alpha = std::clamp(alpha, 0.0f, 1.0f);

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, static_cast<Uint8>(alpha * 255));
        SDL_Rect rect = {200, 200, 400, 200};
        SDL_RenderFillRect(renderer, &rect);

        SDL_RenderPresent(renderer);
        SDL_Delay(16);
    }
}
