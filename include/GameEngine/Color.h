#pragma once

#include <string>

namespace GameEngine {
    class Color {
    public:
        int r{ -1 };
        int g{ -1 };
        int b{ -1 };

        std::string hex;

        //alpha
        const unsigned int maxAlphaValue{ 255 };
        unsigned int a{ maxAlphaValue };

        Color() = default;
        Color(int r, int g, int b);
        Color(int r, int g, int b, char *);
        Color(int r, int g, int b, const char *);
        //Color(int r, int g, int b, const char );
        Color(int r, int g, int b, int alpha);
        Color(const std::string &hex);
        Color(const Color &other);

        Color &operator=(const Color &other);
        bool operator!=(const Color &rhs) const;
        bool operator==(const Color &rhs) const;

        [[nodiscard]] Color alphaPercentage(unsigned int value) const noexcept;
        [[nodiscard]] bool noColor() const noexcept;
    };
}
