#ifndef GRID_H
#define GRID_H

#include "Common.h"
#include <vector>

class Block;

enum OutOfBoundDirection { OutOfBoundsNone, OutOfBoundsLeft, OutOfBoundsRight, OutOfBoundsTop, OutOfBoundsBottom };

struct GridTile {
    bool Occupied = false;
    Color Color = global::Colors.at(ColorDarkGray);
};

class Grid {
public:
    Grid(int rows, int columns);
    void Draw();
    void Clear();
    OutOfBoundDirection IsOutOfBounds(const Block& blocks);
    bool IsCollided(const Block& blocks);
    void AbsorbBlocks(const Block& blocks);
    unsigned int CheckClearRow();
    inline unsigned int GetWidth() const { return static_cast<unsigned int>(m_Tiles[0].size()); }
    inline unsigned int GetHeight() const { return static_cast<unsigned int>(m_Tiles.size()); }

private:
    std::vector<std::vector<GridTile>> m_Tiles;
};

#endif  // GRID_H
