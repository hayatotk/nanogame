#include "Config.hpp"
#include <cstdio>
#include <cstring>
#include <cstdlib>

int key_left   = SDL_SCANCODE_LEFT;
int key_right  = SDL_SCANCODE_RIGHT;
int key_jump   = SDL_SCANCODE_SPACE;
int key_down   = SDL_SCANCODE_DOWN;
int key_run    = SDL_SCANCODE_LSHIFT;
int key_reset  = SDL_SCANCODE_R;
int key_fullscreen = SDL_SCANCODE_F11;

bool show_hitboxes = true;
bool show_debug    = true;
bool show_splash   = true;

int config_window_width  = 800;
int config_window_height = 600;

int window_width   = 800;
int window_height  = 600;
bool fullscreen    = false;

static void trim_line(char* str) {
    char* newline = strchr(str, '\n');
    if (newline) {
        *newline = '\0';
    }
    while (*str == ' ') {
        str++;
    }
}

void load_config(const char* path) {
    FILE* file = fopen(path, "r");
    if (!file) {
        return;
    }

    char line[128];
    while (fgets(line, sizeof(line), file)) {
        trim_line(line);

        char* sep = strchr(line, '=');
        if (!sep) {
            continue;
        }

        *sep++ = '\0';
        trim_line(line);
        trim_line(sep);

        int code = SDL_GetScancodeFromName(sep);

        if (strcmp(line, "left") == 0 && code != SDL_SCANCODE_UNKNOWN) {
            key_left = code;
        } else if (strcmp(line, "right") == 0 && code != SDL_SCANCODE_UNKNOWN) {
            key_right = code;
        } else if (strcmp(line, "jump") == 0 && code != SDL_SCANCODE_UNKNOWN) {
            key_jump = code;
        } else if (strcmp(line, "down") == 0 && code != SDL_SCANCODE_UNKNOWN) {
            key_down = code;
        } else if (strcmp(line, "run") == 0 && code != SDL_SCANCODE_UNKNOWN) {
            key_run = code;
        } else if (strcmp(line, "reset") == 0 && code != SDL_SCANCODE_UNKNOWN) {
            key_reset = code;
        } else if (strcmp(line, "fullscreen_toggle") == 0 && code != SDL_SCANCODE_UNKNOWN) {
            key_fullscreen = code;
        } else if (strcmp(line, "show_hitboxes") == 0) {
            show_hitboxes = (strcmp(sep, "0") != 0);
        } else if (strcmp(line, "show_debug") == 0) {
            show_debug = (strcmp(sep, "0") != 0);
        } else if (strcmp(line, "show_splash") == 0) {
            show_splash = (strcmp(sep, "0") != 0);
        } else if (strcmp(line, "width") == 0) {
            config_window_width = atoi(sep);
            window_width = config_window_width;
        } else if (strcmp(line, "height") == 0) {
            config_window_height = atoi(sep);
            window_height = config_window_height;
        } else if (strcmp(line, "fullscreen") == 0) {
            fullscreen = (strcmp(sep, "0") != 0);
        }
    }

    fclose(file);
}
