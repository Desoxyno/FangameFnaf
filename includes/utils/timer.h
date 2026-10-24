#pragma once

#include <chrono>

struct Timer {
    using clock = std::chrono::steady_clock;

    clock::time_point start_time;

    public:
        Timer() : start_time(clock::now()) {}

        const bool hasTimerEndedYet(std::chrono::duration<double> goal_time) const {
            if ((clock::now() - start_time) >= goal_time) {
                return true;
            }
            else [[likely]] return false;
        }
};