#pragma once
#include "Scene.hpp"
#include "Player.hpp"

struct GameScene : public Scene {
    Player player;
    bool reached_exit;

    GameScene();

    void update() override;
    void render() override;
};
