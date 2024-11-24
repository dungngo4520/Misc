#include "Common.h"
#include <fmt/base.h>

std::map<int, Color> global::Colors = {
    { ColorDarkGray, Color{ 127, 127, 127, 255 } }, { ColorGreen, Color{ 14, 203, 52, 255 } },
    { ColorRed, Color{ 251, 33, 87, 255 } },        { ColorOrange, Color{ 255, 143, 8, 255 } },
    { ColorYellow, Color{ 254, 209, 8, 255 } },     { ColorPurple, Color{ 183, 103, 248, 255 } },
    { ColorCyan, Color{ 9, 235, 241, 255 } },       { ColorBlue, Color{ 8, 170, 246, 255 } },
};

std::map<SpeedType, double> global::Speeds = {
    { SpeedSlow, 1 },
    { SpeedNormal, 0.5 },
    { SpeedFast, 0.3 },
    { SpeedMoveBlockDown, 0.01 },
};

int global::CellSize = 20;

Color global::BackgroundColor = Color{ 29, 31, 32, 255 };
