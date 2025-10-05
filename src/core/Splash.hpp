#pragma once
#include <chrono>

class Splash {
public:
    Splash();
    bool update();

    float getAlpha() const { return alpha; }

private:
    std::chrono::steady_clock::time_point start_time;
    float alpha;
    bool active;
};
