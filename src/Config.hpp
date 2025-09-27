#pragma once
#include <string>

extern std::string key_left_name;
extern std::string key_right_name;
extern std::string key_jump_name;
extern std::string key_down_name;
extern std::string key_run_name;
extern std::string key_reset_name;
extern std::string key_fullscreen_name;

extern bool show_hitboxes;
extern bool show_debug;
extern bool show_splash;

extern int config_window_width;
extern int config_window_height;

extern int window_width;
extern int window_height;
extern bool fullscreen;

void load_config(const char* path);
