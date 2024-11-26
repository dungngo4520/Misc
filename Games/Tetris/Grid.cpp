#include "Grid.h"
#include "Block.h"
#include "Common.h"

#include <algorithm>
#include <cstddef>
#include <fmt/base.h>
#include <fmt/core.h>
#include <raylib.h>

Grid::Grid(int rows, int columns)
{
    m_Tiles.resize(rows);
    for (auto&& row : m_Tiles) {
        row.resize(columns);
    }
}

void Grid::Draw()
{
    for (size_t i = 0; i < m_Tiles.size(); i++) {
        for (size_t j = 0; j < m_Tiles[i].size(); j++) {
            DrawRectangle(
                j * global::CellSize + 1,
                i * global::CellSize + 1,
                global::CellSize - 1,
                global::CellSize - 1,
                m_Tiles[i][j].Color
            );
        }
    }
}

void Grid::Clear()
{
    for (auto&& row : m_Tiles) {
        for (auto&& tile : row) {
            tile = {};
        }
    }
}

OutOfBoundDirection Grid::IsOutOfBounds(const Block& blocks)
{
    auto cells = blocks.GetCells().at(blocks.GetRotate());
    for (auto&& cell : cells) {
        cell += blocks.GetPosition();
        if (cell.x < 0) {
            return OutOfBoundsLeft;
        }
        if (cell.x >= (int)m_Tiles[0].size()) {
            return OutOfBoundsRight;
        }
        if (cell.y < 0) {
            return OutOfBoundsTop;
        }
        if (cell.y >= (int)m_Tiles.size()) {
            return OutOfBoundsBottom;
        }
    }
    return OutOfBoundsNone;
}

bool Grid::IsCollided(const Block& block)
{
    auto cells = block.GetCells().at(block.GetRotate());
    for (auto&& cell : cells) {
        cell += block.GetPosition();
        if (cell.x < 0 || cell.x >= (int)m_Tiles[0].size() || cell.y < 0 || cell.y >= (int)m_Tiles.size() ||
            m_Tiles[cell.y][cell.x].Occupied) {
            return true;
        }
    }
    return false;
}

void Grid::AbsorbBlocks(const Block& blocks)
{
    auto cells = blocks.GetCells().at(blocks.GetRotate());
    for (auto&& cell : cells) {
        cell += blocks.GetPosition();
        if (cell.x < 0 || cell.x >= (int)m_Tiles[0].size() || cell.y < 0 || cell.y >= (int)m_Tiles.size()) {
            continue;
        }
        m_Tiles[cell.y][cell.x] = GridTile{ true, global::Colors.at(blocks.GetColorId()) };
    }
}

unsigned int Grid::CheckClearRow()
{
    int clearCount = 0;
    for (auto i = m_Tiles.size() - 1; i > 0; i--) {
        while (std::all_of(m_Tiles[i].begin(), m_Tiles[i].end(), [](auto&& tile) { return tile.Occupied; })) {
            for (auto j = i; j > 0; j--) {
                for (size_t k = 0; k < m_Tiles[j].size(); k++) {
                    m_Tiles[j][k] = m_Tiles[j - 1][k];
                }
            }
            clearCount++;
        }
    }
    return clearCount;
}
