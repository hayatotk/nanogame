#pragma once
#include <SDL2/SDL.h>

extern int key_left;
extern int key_right;
extern int key_jump;
extern int key_down;
extern int key_run;
extern int key_reset;

extern bool show_hitboxes;
extern bool show_debug;
extern bool show_splash;

void load_config(const char* path);
