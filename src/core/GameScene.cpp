#include "GameScene.hpp"
#include "Level.hpp"
#include "Config.hpp"
#include <cstdio>

extern int level[15][64];
extern int current_level;

struct Camera {
    float x, y;
    int w, h;
};
static Camera camera;

static void render_background(IRenderer& gfx, const Camera& camera, int window_width, int window_height) {
    int tile_size = 32;
    int level_px_w = 128 * tile_size;
    int bg_width = (int)(level_px_w * 1.4f);
    int bg_height = window_height;

    float parallax = 0.5f;
    int offset_x = -(bg_width - level_px_w) / 2;
    float scroll_x = offset_x - camera.x * parallax;

    for (int y = 0; y < bg_height / tile_size + 1; y++) {
        for (int x = 0; x < bg_width / tile_size + 1; x++) {
            int screen_x = (int)(scroll_x + x * tile_size);
            int screen_y = y * tile_size;

            if ((x + y) % 2 == 0) {
                gfx.drawRect(screen_x, screen_y, tile_size, tile_size, 20, 20, 20);
            } else {
                gfx.drawRect(screen_x, screen_y, tile_size, tile_size, 30, 30, 30);
            }
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
    player = init_player(100, 200);
    load_level(0);
    reached_exit = false;

    camera.x = 0;
    camera.y = 0;
    camera.w = window_width;
    camera.h = window_height;
}

void GameScene::update(const InputState& input) {
    handle_input(player, input);
    update_physics(player);

    camera.w = window_width;
    camera.h = window_height;

    camera.x = player.x + 16 - camera.w / 2;
    camera.y = player.y + 16 - camera.h / 2;

    int level_px_w = 64 * 32;
    int level_px_h = 15 * 32;

    if (level_px_w <= camera.w) {
        camera.x = (level_px_w - camera.w) / 2;
    } else {
        if (camera.x < 0) camera.x = 0;
        if (camera.x + camera.w > level_px_w)
            camera.x = level_px_w - camera.w;
    }

    if (level_px_h <= camera.h) {
        camera.y = (level_px_h - camera.h) / 2;
    } else {
        if (camera.y < 0) camera.y = 0;
        if (camera.y + camera.h > level_px_h)
            camera.y = level_px_h - camera.h;
    }

    if (input.reset) {
        load_level(current_level);
        player = init_player(100, 300);
        reached_exit = false;
        return;
    }

    if (check_exit_trigger(player)) {
        int next_level = current_level + 1;
        if (load_level(next_level)) {
            current_level = next_level;
            player = init_player(100, 300);
        } else {
            load_level(0);
            current_level = 0;
            player = init_player(100, 300);
        }
        reached_exit = false;
        return;
    }

    if (player.y > window_height + 200) {
        if (load_level(current_level)) {
            player = init_player(100, 300);
        } else {
            load_level(0);
            current_level = 0;
            player = init_player(100, 300);
        }
        reached_exit = false;
    }
}

void GameScene::render(IRenderer& gfx) {
    render_background(gfx, camera, window_width, window_height);

    for (int ty = camera.y / 32; ty <= (camera.y + camera.h) / 32; ty++) {
        for (int tx = camera.x / 32; tx <= (camera.x + camera.w) / 32; tx++) {
            if (tx >= 0 && tx < 64 && ty >= 0 && ty < 15) {
                if (level[ty][tx] == 1) {
                    gfx.drawRect(tx * 32 - (int)camera.x,
                                 ty * 32 - (int)camera.y,
                                 32, 32, 64, 64, 64);
                    if (show_hitboxes) {
                        gfx.drawRectOutline(tx * 32 - (int)camera.x,
                                            ty * 32 - (int)camera.y,
                                            32, 32, 0, 255, 0);
                    }
                } else if (level[ty][tx] == 2) {
                    if (show_hitboxes) {
                        gfx.drawRectOutline(tx * 32 - (int)camera.x,
                                            ty * 32 - (int)camera.y,
                                            32, 32, 255, 255, 0);
                    }
                }
            }
        }
    }

    gfx.drawRect((int)player.x - (int)camera.x,
                 (int)player.y - (int)camera.y + (player.crouch ? 16 : 0),
                 32, 32 - (player.crouch ? 16 : 0),
                 255, 255, 255);

    if (show_hitboxes) {
        gfx.drawRectOutline((int)player.x - (int)camera.x,
                            (int)player.y - (int)camera.y + (player.crouch ? 16 : 0),
                            32, 32 - (player.crouch ? 16 : 0),
                            0, 0, 255);
    }

    if (show_debug) {
        char buf[128];
        snprintf(buf, sizeof(buf), "x: %.0f y: %.0f vx: %.2f vy: %.2f",
                 player.x, player.y, player.vx, player.vy);
        gfx.drawText(10, 10, buf, 255, 0, 0);

        snprintf(buf, sizeof(buf), "camera: %.0f, %.0f (%dx%d)",
                 camera.x, camera.y, camera.w, camera.h);
        gfx.drawText(10, 30, buf, 255, 0, 0);
    }
}
