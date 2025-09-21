#pragma once

struct Scene {
    virtual ~Scene() = default;
    virtual void update() = 0;
    virtual void render() = 0;
};
