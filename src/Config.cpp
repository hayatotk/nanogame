#include "Config.hpp"
#include <cstdio>
#include <cstring>
#include <cstdlib>

std::string key_left_name       = "LEFT";
std::string key_right_name      = "RIGHT";
std::string key_jump_name       = "SPACE";
std::string key_down_name       = "DOWN";
std::string key_run_name        = "LSHIFT";
std::string key_reset_name      = "R";
std::string key_fullscreen_name = "F11";

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

        if (strcmp(line, "left") == 0) {
            key_left_name = sep;
        } else if (strcmp(line, "right") == 0) {
            key_right_name = sep;
        } else if (strcmp(line, "jump") == 0) {
            key_jump_name = sep;
        } else if (strcmp(line, "down") == 0) {
            key_down_name = sep;
        } else if (strcmp(line, "run") == 0) {
            key_run_name = sep;
        } else if (strcmp(line, "reset") == 0) {
            key_reset_name = sep;
        } else if (strcmp(line, "fullscreen_toggle") == 0) {
            key_fullscreen_name = sep;
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
