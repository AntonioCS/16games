#pragma once

#include <chrono>

namespace GameEngine
{
    class Clock
    {
    public:
        using clock = std::chrono::high_resolution_clock;
        using duration = std::chrono::duration<float, std::milli>;
    private:
        clock::time_point m_start;
    public:
        Clock();
        [[nodiscard]] float elapsedInMs() const;
        [[nodiscard]] float elapsedInSeconds() const;
        void reset();
    };
}
