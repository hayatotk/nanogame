#pragma once
#include "Scene.hpp"
#include "Player.hpp"
#include "InputState.hpp"
#include "IRenderer.hpp"

class GameScene : public Scene {
public:
    GameScene();

    void update(const InputState& input, double dt) override;
    void render(IRenderer& gfx) override;

private:
    Player player;
    bool reached_exit;
};
