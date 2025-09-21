#include "Player.hpp"
#include "Config.hpp"
#include "Level.hpp"
#include <cmath>
#include <initializer_list>

Player init_player(float start_x, float start_y) {
    return {start_x, start_y, 0, 0, 0, 0, 2, 0, 1};
}

void handle_input(Player& player, const Uint8* keys) {
    player.crouch = keys[key_down];
    player.run    = keys[key_run];

    if (keys[key_jump] && !player.prev_jump && player.jumps > 0) {
        player.vy = -12;
        player.jumps--;
        player.prev_jump = 1;
    }
    if (!keys[key_jump]) player.prev_jump = 0;

    float base_speed = 4.0f;
    float move_speed = base_speed;
    if (player.run) move_speed *= 1.5f;
    if (player.crouch) move_speed *= 0.5f;
    if (!player.on_ground) move_speed *= 1.5f;

    float target_vx = 0;
    if (keys[key_left])  target_vx -= move_speed;
    if (keys[key_right]) target_vx += move_speed;

    if (target_vx != 0) player.vx += (target_vx - player.vx) * 0.3f;
    else {
        player.vx *= 0.8f;
        if (fabs(player.vx) < 0.1f) player.vx = 0;
    }
}

void update_physics(Player& player) {
    player.vy += 1;
    if (player.vy > 12) player.vy = 12;

    player.x += player.vx;

    int dir = (player.vx > 0) ? 1 : -1;
    int tile_x = ((int)(player.x + (dir > 0 ? 31 : 0))) / 32;
    int top_y = ((int)player.y + 4) / 32;
    int mid_y = ((int)player.y + 16) / 32;
    int bot_y = ((int)player.y + 28) / 32;

    bool hit = false;
    for (int y_check : {top_y, mid_y, bot_y}) {
        if (tile_x >= 0 && tile_x < 64 &&
            y_check >= 0 && y_check < 15 &&
            level[y_check][tile_x] == 1) {
            hit = true;
            break;
        }
    }
    if (hit) {
        player.x -= player.vx;
        player.vx = 0;
    }

    player.y += player.vy;

    int tx1 = ((int)player.x) / 32;
    int tx2 = ((int)player.x + 31) / 32;
    int foot_y = (int)(player.y + 31) / 32;
    int head_y = (int)(player.y + 4) / 32;

    bool foot_block = false, head_block = false;

    if (foot_y >= 0 && foot_y < 15) {
        if ((tx1 >= 0 && tx1 < 64 && level[foot_y][tx1] == 1) ||
            (tx2 >= 0 && tx2 < 64 && level[foot_y][tx2] == 1)) {
            foot_block = true;
        }
    }
    if (head_y >= 0 && head_y < 15) {
        if ((tx1 >= 0 && tx1 < 64 && level[head_y][tx1] == 1) ||
            (tx2 >= 0 && tx2 < 64 && level[head_y][tx2] == 1)) {
            head_block = true;
        }
    }

    if (foot_block && !head_block) {
        player.y = foot_y * 32 - 31;
        player.vy = 0;
        player.jumps = 2;
        player.on_ground = 1;
    } else {
        player.on_ground = 0;
    }

    if (head_block && player.vy < 0) {
        player.y = (head_y + 1) * 32 - 4;
        player.vy = 0;
    }

    if (player.x < 0) player.x = 0;
    if (player.y > 799) {
        player = init_player(100, 100);
    }
}

void render_player(const Player& player, SDL_Renderer* renderer, bool show_hitboxes) {
    SDL_Rect rect = {
        (int)player.x % 800,
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
