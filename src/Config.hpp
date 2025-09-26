#pragma once
#include <SDL2/SDL.h>

extern int key_left;
extern int key_right;
extern int key_jump;
extern int key_down;
extern int key_run;
extern int key_reset;
extern int key_fullscreen;
extern int window_width;
extern int window_height;
extern int config_window_width;
extern int config_window_height;


extern bool show_hitboxes;
extern bool show_debug;
extern bool show_splash;
extern bool fullscreen;

void load_config(const char* path);
