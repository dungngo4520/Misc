#include "Block.h"
#include "Common.h"
#include "grid.h"
#include <climits>
#include <fmt/ostream.h>
#include <raylib.h>
#include <vector>

Block::Block(const std::map<enum Rotate, std::vector<Position>>& cells) :
    m_Rotate(Rotate0),
    m_Position({ 0, 0 }),
    m_Cells(cells)
{
}

void Block::Draw()
{
    auto cells = m_Cells.at(m_Rotate);
    for (auto&& cell : cells) {
        cell += m_Position;
        DrawRectangle(
            cell.x * global::CellSize + 1,
            cell.y * global::CellSize + 1,
            global::CellSize - 1,
            global::CellSize - 1,
            global::Colors.at(GetColorId())
        );
    }
}

void Block::Rotate() { m_Rotate = (enum Rotate)((m_Rotate + 1) % RotateMax); }

void Block::Move(int x, int y) { m_Position += Position{ x, y }; }

unsigned int Block::GetWidth() const
{
    auto cells = m_Cells.at(m_Rotate);
    int maxX = 0, minX = UINT_MAX;
    for (auto&& cell : cells) {
        maxX = std::max(maxX, cell.x);
        minX = std::min(minX, cell.x);
    }
    return maxX - minX + 1;
}

unsigned int Block::GetHeight() const
{
    auto cells = m_Cells.at(m_Rotate);
    int maxY = 0, minY = UINT_MAX;
    for (auto&& cell : cells) {
        maxY = std::max(maxY, cell.y);
        minY = std::min(minY, cell.y);
    }
    return maxY - minY + 1;
}
