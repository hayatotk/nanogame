#include "GameScene.hpp"
#include "Config.hpp"
#include "Level.hpp"
#include "Render.hpp"

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <cstdio>

// глобальные ссылки из main.cpp
extern SDL_Renderer* g_renderer;
extern TTF_Font* g_font;

static void render_background(const Player& player) {
    int tile_size = 32;
    int level_width = 64 * tile_size; // 2048px
    int bg_width = (int)(level_width * 1.4f); // +20%
    int bg_height = 600;

    float parallax = 0.5f;
    int offset_x = -(bg_width - level_width) / 2;
    float scroll_x = offset_x - player.x * parallax;

    for (int y = 0; y < bg_height / tile_size + 1; y++) {
        for (int x = 0; x < bg_width / tile_size + 1; x++) {
            int screen_x = (int)(scroll_x + x * tile_size);
            int screen_y = y * tile_size;

            if ((x + y) % 2 == 0) {
                SDL_SetRenderDrawColor(g_renderer, 20, 20, 20, 255);
            } else {
                SDL_SetRenderDrawColor(g_renderer, 30, 30, 30, 255);
            }

            SDL_Rect rect = {screen_x, screen_y, tile_size, tile_size};
            SDL_RenderFillRect(g_renderer, &rect);
        }
    }
}

static bool check_exit_trigger(const Player& player) {
    int left   = (int)player.x / 32;
    int right  = ((int)player.x + 31) / 32;
    int top    = (int)player.y / 32;
    int bottom = (int)(player.y + 31) / 32;

    for (int ty = top; ty <= bottom; ty++) {
        for (int tx = left; tx <= right; tx++) {
            if (tx >= 0 && tx < 64 && ty >= 0 && ty < 15) {
                if (level[ty][tx] == 2) {
                    return true;
                }
            }
        }
    }
    return false;
}

GameScene::GameScene() {
    player = init_player(100, 100);
    load_level(0);
    reached_exit = false;
}

void GameScene::update() {
    SDL_PumpEvents();
    const Uint8* keys = SDL_GetKeyboardState(nullptr);
    handle_input(player, keys);
    update_physics(player);

    if (keys[key_reset]) {
        load_level(current_level);
        player = init_player(100, 100);
        reached_exit = false;
        return;
    }

    if (check_exit_trigger(player)) {
        int next_level = current_level + 1;
        if (load_level(next_level)) {
            current_level = next_level;
            player = init_player(100, 100);
        } else {
            load_level(0);
            current_level = 0;
            player = init_player(100, 100);
        }
        reached_exit = false;
        return;
    }

    if (player.y > 799) {
        if (load_level(current_level)) {
            player = init_player(100, 100);
        } else {
            load_level(0);
            current_level = 0;
            player = init_player(100, 100);
        }
        reached_exit = false;
    }
}



void GameScene::render() {
    render_background(player);

    int screen = (int)player.x / 800;
        for (int ty = 0; ty < 15; ty++) {
            for (int tx = screen * 25; tx < (screen + 1) * 25; tx++) {
                if (tx >= 0 && tx < 64) {
                    SDL_Rect block = {(tx % 25) * 32, ty * 32, 32, 32};
                
                    if (level[ty][tx] == 1) {
                        SDL_SetRenderDrawColor(g_renderer, 64, 64, 64, 255);
                        SDL_RenderFillRect(g_renderer, &block);
                    
                        if (show_hitboxes) {
                            SDL_SetRenderDrawColor(g_renderer, 0, 255, 0, 255);
                            SDL_RenderDrawRect(g_renderer, &block);
                        }
                    } 
                    else if (level[ty][tx] == 2) {
                        if (show_hitboxes) {
                            SDL_SetRenderDrawColor(g_renderer, 255, 255, 0, 255);
                            SDL_RenderDrawRect(g_renderer, &block);
                        }
                    }
                }
            }
        }


    render_player(player, g_renderer, show_hitboxes);

    if (show_debug) {
        char buf_x[64], buf_y[64], buf_screen[64];
        char buf_vx[64], buf_vy[64], buf_jumps[64], buf_ground[64], buf_lvl[64], buf_done[64];

        snprintf(buf_x, sizeof(buf_x), "x: %.0f", player.x);
        snprintf(buf_y, sizeof(buf_y), "y: %.0f", player.y);
        snprintf(buf_screen, sizeof(buf_screen), "screen: %d", (int)player.x / 800);
        snprintf(buf_vx, sizeof(buf_vx), "vx: %.2f", player.vx);
        snprintf(buf_vy, sizeof(buf_vy), "vy: %.2f", player.vy);
        snprintf(buf_jumps, sizeof(buf_jumps), "jumps: %d", player.jumps);
        snprintf(buf_ground, sizeof(buf_ground), "ground: %d", player.on_ground);
        snprintf(buf_lvl, sizeof(buf_lvl), "level: %d", current_level);
        snprintf(buf_done, sizeof(buf_lvl), "is_done: %d", reached_exit);

        draw_text(g_renderer, g_font, 10, 10, buf_x);
        draw_text(g_renderer, g_font, 10, 30, buf_y);
        draw_text(g_renderer, g_font, 10, 50, buf_screen);
        draw_text(g_renderer, g_font, 10, 70, buf_vx);
        draw_text(g_renderer, g_font, 10, 90, buf_vy);
        draw_text(g_renderer, g_font, 10, 110, buf_jumps);
        draw_text(g_renderer, g_font, 10, 130, buf_ground);
        draw_text(g_renderer, g_font, 10, 150, buf_lvl);
        draw_text(g_renderer, g_font, 10, 170, buf_done);
    }

    SDL_RenderPresent(g_renderer);
}
