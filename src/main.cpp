#include "Config.hpp"
#include "GameScene.hpp"
#include "Scene.hpp"
#include "core/InputState.hpp"

#ifdef USE_SDL
    #include <SDL2/SDL.h>
    #include <SDL2/SDL_ttf.h>
    #include "platform/SDL_uni/Input.hpp"
    #include "platform/SDL_uni/Renderer.hpp"
    #include "platform/SDL_uni/PlayerRender.hpp"
    #include "platform/SDL_uni/SplashRender.hpp"

    SDL_Renderer* g_renderer = nullptr;
    TTF_Font* g_font = nullptr;
#endif

int main() {
    load_config("config.ini");

#ifdef USE_SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        SDL_Log("SDL_Init failed: %s", SDL_GetError());
        return 1;
    }
    if (TTF_Init() < 0) {
        SDL_Log("TTF_Init failed: %s", TTF_GetError());
        return 1;
    }

    Uint32 window_flags = fullscreen ? SDL_WINDOW_FULLSCREEN_DESKTOP : 0;


    if (show_splash) {
        Splash splash;

        while (splash.update()) {
            render_splash_sdl(g_renderer, splash);
            SDL_Delay(16); // ~60 FPS
        }
    }


    SDL_Window* window = SDL_CreateWindow("p",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        window_width, window_height, window_flags);

    if (!window) {
        SDL_Log("SDL_CreateWindow failed: %s", SDL_GetError());
        return 1;
    }

    Uint32 render_flags = SDL_RENDERER_ACCELERATED;
    if (vsync) render_flags |= SDL_RENDERER_PRESENTVSYNC;

        g_renderer = SDL_CreateRenderer(window, -1, render_flags);

    if (!g_renderer) {
        SDL_Log("SDL_CreateRenderer failed: %s", SDL_GetError());
        return 1;
    }

    SDL_GetWindowSize(window, &window_width, &window_height);

    g_font = TTF_OpenFont("test.ttf", 24);
    if (!g_font) {
        SDL_Log("Failed to load font: %s", TTF_GetError());
        show_debug = false;
    }

    SDLRenderer gfx(g_renderer, g_font);
#endif

    Scene* current_scene = new GameScene();
    bool quit = false;

#ifdef USE_SDL
    SDL_Event event;
#endif

#ifdef USE_SDL
    Uint64 prev = SDL_GetPerformanceCounter();
    const double freq = (double)SDL_GetPerformanceFrequency();
#endif

    while (!quit) {
#ifdef USE_SDL
        Uint64 now = SDL_GetPerformanceCounter();
        double deltaTime = (double)(now - prev) / freq;
        prev = now;

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = true;
            } else if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.scancode == get_fullscreen_scancode()) {
                    Uint32 flags = SDL_GetWindowFlags(window);
                    if (flags & SDL_WINDOW_FULLSCREEN_DESKTOP) {
                        SDL_SetWindowFullscreen(window, 0);
                        SDL_SetWindowSize(window, config_window_width, config_window_height);

                        int w, h;
                        SDL_GetWindowSize(window, &w, &h);
                        window_width = w;
                        window_height = h;
                    } else {
                        SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP);

                        int w, h;
                        SDL_GetWindowSize(window, &w, &h);
                        window_width = w;
                        window_height = h;
                    }
                }
            } else if (event.type == SDL_WINDOWEVENT &&
                       event.window.event == SDL_WINDOWEVENT_RESIZED) {
                SDL_GetWindowSize(window, &window_width, &window_height);
            }
        }

        SDL_PumpEvents();
        InputState input = get_input_from_sdl();

        current_scene->update(input, deltaTime);
        gfx.clear(0, 0, 0);
        current_scene->render(gfx);
        gfx.present();
#endif

#ifdef USE_PSP
        // TODO: wii or psp or whatever --- IGNORE ---
#endif
    }

    delete current_scene;

#ifdef USE_SDL
    if (g_font) TTF_CloseFont(g_font);
    SDL_DestroyRenderer(g_renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();
#endif

    return 0;
}
