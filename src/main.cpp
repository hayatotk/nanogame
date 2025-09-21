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

    SDL_Window* window = SDL_CreateWindow("p",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, 0);
    g_renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    g_font = TTF_OpenFont("test.ttf", 24);

    if (show_splash) run_splash(g_renderer, g_font);

    Scene* current_scene = new GameScene();

    bool quit = false;
    SDL_Event event;
    while (!quit) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) quit = true;
        }
        current_scene->update();
        current_scene->render();
    }

    delete current_scene;
    return 0;
}
