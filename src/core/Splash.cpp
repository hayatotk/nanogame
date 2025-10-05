#include "Splash.hpp"
#include <algorithm>

Splash::Splash() {
    start_time = std::chrono::steady_clock::now();
    alpha = 0.0f;
    active = true;
}

bool Splash::update() {
    if (!active) return false;

    auto now = std::chrono::steady_clock::now();
    auto elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(now - start_time).count();

    if (elapsed_ms < 500) {
        // fade in (0.5s)
        alpha = static_cast<float>(elapsed_ms) / 500.0f;
    } else if (elapsed_ms < 1500) {
        // hold (1s)
        alpha = 1.0f;
    } else if (elapsed_ms < 2500) {
        // fade out (1s)
        alpha = 1.0f - static_cast<float>(elapsed_ms - 1500) / 1000.0f;
    } else {
        alpha = 0.0f;
        active = false;
        return false;
    }

    alpha = std::clamp(alpha, 0.0f, 1.0f);
    return true;
}
