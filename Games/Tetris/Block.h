#ifndef BLOCK_H
#define BLOCK_H

#include "Common.h"
#include <atomic>
#include <map>
#include <vector>

class Block {
    friend class Grid;

public:
    enum BlockId { BlockIdI, BlockIdJ, BlockIdL, BlockIdO, BlockIdS, BlockIdT, BlockIdZ };
    enum Rotate { Rotate0, Rotate90, Rotate180, Rotate270, RotateMax };

public:
    Block(const std::map<enum Rotate, std::vector<Position>>& cells);
    void Draw();
    void Rotate();
    void Move(int x, int y);

    unsigned int GetWidth() const;
    unsigned int GetHeight() const;

protected:
    virtual ColorId GetColorId() const { return ColorDarkGray; }

    std::atomic<enum Rotate> m_rotate;
    Position m_position;
    std::map<enum Rotate, std::vector<Position>> m_cells;
};

class BlockL : public Block {
public:
    inline BlockL() :
        Block({
            { Rotate0, { { 0, 0 }, { 1, 0 }, { 1, 1 }, { 1, 2 } } },
            { Rotate90, { { 0, 0 }, { 0, 1 }, { 1, 0 }, { 2, 0 } } },
            { Rotate180, { { 0, 0 }, { 0, 1 }, { 0, 2 }, { 1, 2 } } },
            { Rotate270, { { 0, 1 }, { 1, 1 }, { 2, 0 }, { 2, 1 } } },
        })
    {
    }

private:
    inline ColorId GetColorId() const override { return ColorGreen; }
};

class BlockJ : public Block {
public:
    inline BlockJ() :
        Block({
            { Rotate0, { { 0, 2 }, { 1, 0 }, { 1, 1 }, { 1, 2 } } },
            { Rotate90, { { 0, 0 }, { 1, 0 }, { 2, 0 }, { 2, 1 } } },
            { Rotate180, { { 0, 0 }, { 0, 1 }, { 0, 2 }, { 1, 0 } } },
            { Rotate270, { { 0, 0 }, { 0, 1 }, { 1, 1 }, { 2, 1 } } },
        })
    {
    }

private:
    inline ColorId GetColorId() const override { return ColorRed; }
};

class BlockI : public Block {
public:
    inline BlockI() :
        Block({
            { Rotate0, { { 1, 0 }, { 1, 1 }, { 1, 2 }, { 1, 3 } } },
            { Rotate90, { { 0, 2 }, { 1, 2 }, { 2, 2 }, { 3, 2 } } },
            { Rotate180, { { 1, 0 }, { 1, 1 }, { 1, 2 }, { 1, 3 } } },
            { Rotate270, { { 0, 2 }, { 1, 2 }, { 2, 2 }, { 3, 2 } } },
        })
    {
    }

private:
    inline ColorId GetColorId() const override { return ColorPurple; }
};

class BlockO : public Block {
public:
    inline BlockO() :
        Block({
            { Rotate0, { { 0, 0 }, { 0, 1 }, { 1, 0 }, { 1, 1 } } },
            { Rotate90, { { 0, 0 }, { 0, 1 }, { 1, 0 }, { 1, 1 } } },
            { Rotate180, { { 0, 0 }, { 0, 1 }, { 1, 0 }, { 1, 1 } } },
            { Rotate270, { { 0, 0 }, { 0, 1 }, { 1, 0 }, { 1, 1 } } },
        })
    {
    }

private:
    inline ColorId GetColorId() const override { return ColorCyan; }
};

class BlockS : public Block {
public:
    inline BlockS() :
        Block({
            { Rotate0, { { 0, 1 }, { 0, 2 }, { 1, 0 }, { 1, 1 } } },
            { Rotate90, { { 0, 0 }, { 1, 0 }, { 1, 1 }, { 2, 1 } } },
            { Rotate180, { { 0, 1 }, { 0, 2 }, { 1, 0 }, { 1, 1 } } },
            { Rotate270, { { 0, 0 }, { 1, 0 }, { 1, 1 }, { 2, 1 } } },
        })
    {
    }

private:
    inline ColorId GetColorId() const override { return ColorBlue; }
};

class BlockZ : public Block {
public:
    inline BlockZ() :
        Block({
            { Rotate0, { { 0, 0 }, { 0, 1 }, { 1, 1 }, { 1, 2 } } },
            { Rotate90, { { 0, 1 }, { 1, 0 }, { 1, 1 }, { 2, 0 } } },
            { Rotate180, { { 0, 0 }, { 0, 1 }, { 1, 1 }, { 1, 2 } } },
            { Rotate270, { { 0, 1 }, { 1, 0 }, { 1, 1 }, { 2, 0 } } },
        })
    {
    }

private:
    inline ColorId GetColorId() const override { return ColorOrange; }
};

class BlockT : public Block {
public:
    inline BlockT() :
        Block({
            { Rotate0, { { 0, 1 }, { 1, 0 }, { 1, 1 }, { 1, 2 } } },
            { Rotate90, { { 0, 0 }, { 1, 0 }, { 1, 1 }, { 2, 0 } } },
            { Rotate180, { { 0, 0 }, { 0, 1 }, { 0, 2 }, { 1, 1 } } },
            { Rotate270, { { 0, 1 }, { 1, 0 }, { 1, 1 }, { 2, 1 } } },
        })
    {
    }

private:
    inline ColorId GetColorId() const override { return ColorYellow; }
};

#endif  // BLOCK_H
