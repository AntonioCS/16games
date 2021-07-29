#include <GameEngine/Clock.h>

namespace GameEngine
{
    Clock::Clock()
    {
        reset();
    }

    float Clock::elapsedInMs() const
    {
        const duration elapsed{ clock::now() - m_start };
        return elapsed.count();
    }

    float Clock::elapsedInSeconds() const
    {
        return elapsedInMs() / 1000.f;
    }

    void Clock::reset()
    {
        m_start = clock::now();
    }
}

