#ifndef GRID_H
#define GRID_H

#include "Common.h"
#include <vector>

class Block;

enum OutOfBoundDirection { OutOfBoundsNone, OutOfBoundsLeft, OutOfBoundsRight, OutOfBoundsTop, OutOfBoundsBottom };

struct GridTile {
    bool Occupied = false;
    Color Color = global::Colors[ColorDarkGray];
};

class Grid {
public:
    Grid(int rows, int columns);

    void Draw();

    OutOfBoundDirection IsOutOfBounds(const Block& blocks);
    bool IsCollided(const Block& blocks);

    void AbsorbBlocks(const Block& blocks);
    int CheckClearRow();

    inline unsigned int GetWidth() const { return static_cast<unsigned int>(m_grids[0].size()); }
    inline unsigned int GetHeight() const { return static_cast<unsigned int>(m_grids.size()); }

private:
    std::vector<std::vector<GridTile>> m_grids;
};

#endif  // GRID_H
