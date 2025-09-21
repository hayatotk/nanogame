#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

void draw_text(SDL_Renderer* renderer, TTF_Font* font, int x, int y, const char* message);
