#include "Grid.h"
#include "Block.h"
#include "Common.h"

#include <algorithm>
#include <fmt/base.h>
#include <fmt/core.h>
#include <raylib.h>

Grid::Grid(int rows, int columns)
{
    m_grids.resize(rows);
    for (auto&& row : m_grids) {
        row.resize(columns);
    }
}

void Grid::Draw()
{
    for (int i = 0; i < m_grids.size(); i++) {
        for (int j = 0; j < m_grids[i].size(); j++) {
            DrawRectangle(
                j * global::CellSize + 1,
                i * global::CellSize + 1,
                global::CellSize - 1,
                global::CellSize - 1,
                m_grids[i][j].Color
            );
        }
    }
}

OutOfBoundDirection Grid::IsOutOfBounds(const Block& blocks)
{
    auto cells = blocks.m_cells.at(blocks.m_rotate);
    for (auto&& cell : cells) {
        cell += blocks.m_position;
        if (cell.x < 0) {
            return OutOfBoundsLeft;
        }
        if (cell.x >= m_grids[0].size()) {
            return OutOfBoundsRight;
        }
        if (cell.y < 0) {
            return OutOfBoundsTop;
        }
        if (cell.y >= m_grids.size()) {
            return OutOfBoundsBottom;
        }
    }
    return OutOfBoundsNone;
}

bool Grid::IsCollided(const Block& blocks)
{
    auto cells = blocks.m_cells.at(blocks.m_rotate);
    for (auto&& cell : cells) {
        cell += blocks.m_position;
        if (cell.x < 0 || cell.x >= m_grids[0].size() || cell.y < 0 || cell.y >= m_grids.size() ||
            m_grids[cell.y][cell.x].Occupied) {
            return true;
        }
    }
    return false;
}

void Grid::AbsorbBlocks(const Block& blocks)
{
    auto cells = blocks.m_cells.at(blocks.m_rotate);
    for (auto&& cell : cells) {
        cell += blocks.m_position;
        m_grids[cell.y][cell.x] = GridTile{ true, global::Colors[blocks.GetColorId()] };
    }
}

int Grid::CheckClearRow()
{
    int clearCount = 0;
    for (auto i = m_grids.size() - 1; i > 0; i--) {
        while (std::all_of(m_grids[i].begin(), m_grids[i].end(), [](auto&& tile) { return tile.Occupied; })) {
            for (auto j = i; j > 0; j--) {
                for (auto k = 0; k < m_grids[j].size(); k++) {
                    m_grids[j][k] = m_grids[j - 1][k];
                }
            }
            clearCount++;
        }
    }
    return clearCount;
}
