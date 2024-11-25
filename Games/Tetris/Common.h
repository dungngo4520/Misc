#ifndef COMMON_H
#define COMMON_H

#include <raylib.h>
#include <map>

enum ColorId { ColorDarkGray, ColorGreen, ColorRed, ColorOrange, ColorYellow, ColorPurple, ColorCyan, ColorBlue };
enum SpeedType { SpeedSlow, SpeedNormal, SpeedFast, SpeedMoveBlockDown };

struct Position {
    int x;
    int y;

    Position& operator+=(const Position& rhs)
    {
        this->x += rhs.x;
        this->y += rhs.y;
        return *this;
    }
    Position operator+(const Position& rhs) const { return Position{ this->x + rhs.x, this->y + rhs.y }; }
};

namespace global {
    const std::map<int, Color> Colors = {
        { ColorDarkGray, Color{ 127, 127, 127, 255 } }, { ColorGreen, Color{ 14, 203, 52, 255 } },
        { ColorRed, Color{ 251, 33, 87, 255 } },        { ColorOrange, Color{ 255, 143, 8, 255 } },
        { ColorYellow, Color{ 254, 209, 8, 255 } },     { ColorPurple, Color{ 183, 103, 248, 255 } },
        { ColorCyan, Color{ 9, 235, 241, 255 } },       { ColorBlue, Color{ 8, 170, 246, 255 } },
    };
    const std::map<SpeedType, double> Speeds = {
        { SpeedSlow, 1 },
        { SpeedNormal, 0.5 },
        { SpeedFast, 0.3 },
        { SpeedMoveBlockDown, 0.01 },
    };
    const int CellSize = 20;
    const Color BackgroundColor = Color{ 29, 31, 32, 255 };
}  // namespace global

#endif  // COMMON_H
