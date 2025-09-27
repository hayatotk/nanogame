#pragma once
#include <string>
#include <cstdint>

class IRenderer {
public:
    virtual ~IRenderer() = default;

    virtual void clear(uint8_t r, uint8_t g, uint8_t b) = 0;

    virtual void drawRect(int x, int y, int w, int h,
                          uint8_t r, uint8_t g, uint8_t b) = 0;

    virtual void drawRectOutline(int x, int y, int w, int h,
                                 uint8_t r, uint8_t g, uint8_t b) = 0;

    virtual void drawText(int x, int y, const std::string& msg,
                          uint8_t r, uint8_t g, uint8_t b) = 0;

    virtual void present() = 0;
};
