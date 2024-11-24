#include "Block.h"
#include "Common.h"
#include "grid.h"
#include <climits>
#include <fmt/ostream.h>
#include <raylib.h>
#include <vector>

Block::Block(const std::map<enum Rotate, std::vector<Position>>& cells) :
    m_rotate(Rotate0),
    m_position({ 0, 0 }),
    m_cells(cells)
{
}

void Block::Draw()
{
    auto cells = m_cells.at(m_rotate);
    for (auto&& cell : cells) {
        cell += m_position;
        DrawRectangle(
            cell.x * global::CellSize + 1,
            cell.y * global::CellSize + 1,
            global::CellSize - 1,
            global::CellSize - 1,
            global::Colors[GetColorId()]
        );
    }
}

void Block::Rotate() { m_rotate = (enum Rotate)((m_rotate + 1) % RotateMax); }

void Block::Move(int x, int y) { m_position += Position{ x, y }; }

unsigned int Block::GetWidth() const
{
    auto cells = m_cells.at(m_rotate);
    int maxX = 0, minX = UINT_MAX;
    for (auto&& cell : cells) {
        maxX = std::max(maxX, cell.x);
        minX = std::min(minX, cell.x);
    }
    return maxX - minX + 1;
}

unsigned int Block::GetHeight() const
{
    auto cells = m_cells.at(m_rotate);
    int maxY = 0, minY = UINT_MAX;
    for (auto&& cell : cells) {
        maxY = std::max(maxY, cell.y);
        minY = std::min(minY, cell.y);
    }
    return maxY - minY + 1;
}
