#pragma once
#include "InputState.hpp"
#include "IRenderer.hpp"

class Scene {
public:
    virtual ~Scene() = default;

    virtual void update(const InputState& input) = 0;
    virtual void render(IRenderer& gfx) = 0;
};
