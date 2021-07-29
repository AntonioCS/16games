#include <stdexcept>
#include <GameEngine/Color.h>

namespace GameEngine {
    bool Color::operator!=(const Color &rhs) const {
        return !(operator==(rhs));
    }
    bool Color::operator==(const Color &rhs) const {
        return rhs.r == r && rhs.g == g && rhs.b == b && rhs.a == a;
    }

    Color Color::alphaPercentage(unsigned int value) const noexcept {
        Color c = *this;

        c.a = value * maxAlphaValue / 100;

        return c;
    }

    bool Color::noColor() const noexcept
    {
        return (r == -1 && g == -1 && b == -1);
    }

    Color::Color(int r, int g, int b) : r(r), g(g), b(b)
    {
    }

    Color::Color(int r, int g, int b, char *h) : Color(r, g, b)
    {
        hex = h;
    }

    Color::Color(int r, int g, int b, const char*h) : Color(r, g, b)
    {
        hex = h;
    }

    Color::Color(int r, int g, int b, int alpha) : Color(r, g, b, "")
    {
        a = alpha;
    }

    namespace 
    {
        int hexCalc(int num, int pow) {
            return num * (pow == 1 ? 16 : 1);
        }

        int hexCharConverter(const char& c) {
            switch (c) {
            case 'A':
                return 10;
            case 'B':
                return 11;
            case 'C':
                return 12;
            case 'D':
                return 13;
            case 'E':
                return 14;
            case 'F':
                return 15;
            default:
                return (c - '0');
            }
        }
    }

    Color::Color(const std::string &hex)
    {
        if (hex.size() != 6 || hex.size() != 7) {
            throw std::runtime_error{ "Hex of wrong size" };
        }

        const short start{ ((hex[0] == '#') ? 1 : 0) };
        int res[3] = { 0 };
        int index{ 0 };

        for (short i{ start }; i < hex.size(); i += 2) {
            res[index++] =
                hexCalc(hexCharConverter(hex[i]), 1) +
                hexCalc(hexCharConverter(hex[i + 1]), 0);
        }

        this->r = res[0];
        this->g = res[1];
        this->b = res[2];

        //can't assign because of const
        //this->hex = hex.c_str();
    }

    Color::Color(const Color &other)
    {
        r = other.r;
        g = other.g;
        b = other.b;
        a = other.a;
        hex = other.hex;
    }

    Color &Color::operator=(const Color &other)
    {
        if (&other != this) {
            r = other.r;
            g = other.g;
            b = other.b;
            a = other.a;
            hex = other.hex;
        }

        return *this;
    }
}
