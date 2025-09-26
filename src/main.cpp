#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "Config.hpp"
#include "Splash.hpp"
#include "GameScene.hpp"

SDL_Renderer* g_renderer = nullptr;
TTF_Font* g_font = nullptr;

int main() {
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();
    load_config("config.ini");

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "0");

    Uint32 window_flags = 0;

    if (fullscreen) {
        window_flags |= SDL_WINDOW_FULLSCREEN_DESKTOP;
    }

    SDL_Window* window = SDL_CreateWindow("p",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        window_width, window_height, window_flags);

    g_renderer = SDL_CreateRenderer(window, -1,
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    SDL_GetWindowSize(window, &window_width, &window_height);

    g_font = TTF_OpenFont("test.ttf", 24);

    if (show_splash) {
        run_splash(g_renderer, g_font);
    }

    Scene* current_scene = new GameScene();

    bool quit = false;
    SDL_Event event;
    while (!quit) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = true;
            } else if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.scancode == key_fullscreen) {
                    Uint32 flags = SDL_GetWindowFlags(window);
                    if (flags & SDL_WINDOW_FULLSCREEN_DESKTOP) {
                        SDL_SetWindowFullscreen(window, 0);
                        SDL_SetWindowSize(window, config_window_width, config_window_height);

                        int w, h;
                        SDL_GetWindowSize(window, &w, &h);
                        window_width = w;
                        window_height = h;

                        printf("Fullscreen OFF (%dx%d)\n", window_width, window_height);
                    } else {
                        SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP);

                        int w, h;
                        SDL_GetWindowSize(window, &w, &h);
                        window_width = w;
                        window_height = h;

                        printf("Fullscreen ON (%dx%d)\n", window_width, window_height);
                    }
                }
            } else if (event.type == SDL_WINDOWEVENT &&
                       event.window.event == SDL_WINDOWEVENT_RESIZED) {
                SDL_GetWindowSize(window, &window_width, &window_height);
                printf("Window resized to %dx%d\n", window_width, window_height);
            }
        }

        current_scene->update();
        current_scene->render();
    }

    delete current_scene;

    if (g_font) {
        TTF_CloseFont(g_font);
    }
    SDL_DestroyRenderer(g_renderer);
    SDL_DestroyWindow(window);

    TTF_Quit();
    SDL_Quit();

    return 0;
}
