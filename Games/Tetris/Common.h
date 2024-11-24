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
    extern std::map<int, Color> Colors;
    extern std::map<SpeedType, double> Speeds;
    extern int CellSize;
    extern Color BackgroundColor;
}  // namespace global

#endif  // COMMON_H
