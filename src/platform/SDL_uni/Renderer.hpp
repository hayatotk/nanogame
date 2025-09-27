#pragma once
#include "../core/IRenderer.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>

class SDLRenderer : public IRenderer {
public:
    SDLRenderer(SDL_Renderer* r, TTF_Font* f);
    ~SDLRenderer() = default;

    void clear(uint8_t r, uint8_t g, uint8_t b) override;
    void drawRect(int x, int y, int w, int h,
                  uint8_t r, uint8_t g, uint8_t b) override;
    void drawRectOutline(int x, int y, int w, int h,
                         uint8_t r, uint8_t g, uint8_t b) override;
    void drawText(int x, int y, const std::string& msg,
                  uint8_t r, uint8_t g, uint8_t b) override;
    void present() override;

private:
    SDL_Renderer* renderer;
    TTF_Font* font;
};
