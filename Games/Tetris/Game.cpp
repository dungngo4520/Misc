#include "Game.h"
#include "Block.h"
#include "Common.h"
#include "grid.h"

#include <algorithm>
#include <fmt/ostream.h>
#include <fmt/std.h>
#include <functional>
#include <memory>
#include <mutex>
#include <random>
#include <raylib.h>
#include <thread>
#include <vector>

Game::Game(int FPS) :
    m_grid(20, 10),
    m_currentBlock(GetRandomBlock()),
    m_currentSpeed(SpeedNormal),
    m_score(0),
    m_worker([&]() { Worker(); }),
    m_signals({
        { SignalStop, false },
        { SignalKeyDownPressed, false },
    }),
    m_intervalWorks({ { IntervalWorkMovingBlockDown, { global::Speeds[m_currentSpeed], [&]() { MoveBlockDown(); } } } })
{
    SetTargetFPS(60);
    MoveBlockCenter();
}

Game::~Game()
{
    NotifySignal(SignalStop, true);
    m_worker.join();
}

void Game::Draw()
{
    m_grid.Draw();
    m_currentBlock->Draw();
}

void Test() {};

void Game::HandleInput()
{
    switch (GetKeyPressed()) {
        case KEY_LEFT:
            MoveBlockLeft();
            break;
        case KEY_RIGHT:
            MoveBlockRight();
            break;
        case KEY_DOWN:
            NotifySignal(SignalKeyDownPressed, true);
            break;
        case KEY_UP:
            m_currentBlock->Rotate();
            Calibrate();
            break;
    }
}

void Game::Loop()
{
    double lastTime = GetTime();
    auto CheckWork = [&]() {
        double currentTime = GetTime();
        for (auto&& work : m_intervalWorks) {
            if (currentTime - lastTime >= work.second.intervalSecond) {
                work.second.work();
                lastTime = currentTime;
            }
        }
    };

    while (!WindowShouldClose()) {
        CheckWork();
        HandleInput();
        BeginDrawing();
        ClearBackground(global::BackgroundColor);
        Draw();
        EndDrawing();
    }
}

void Game::MoveBlockCenter() { m_currentBlock->Move((m_grid.GetWidth() - m_currentBlock->GetWidth()) / 2, 0); }

void Game::MoveBlockLeft()
{
    m_currentBlock->Move(-1, 0);
    Calibrate();
    if (m_grid.IsCollided(*m_currentBlock)) {
        m_currentBlock->Move(1, 0);
    }
}

void Game::MoveBlockRight()
{
    m_currentBlock->Move(1, 0);
    Calibrate();
    if (m_grid.IsCollided(*m_currentBlock)) {
        m_currentBlock->Move(-1, 0);
    }
}

void Game::MoveBlockDown()
{
    m_currentBlock->Move(0, 1);

    if (m_grid.IsCollided(*m_currentBlock)) {
        m_currentBlock->Move(0, -1);
        NotifySignal(SignalKeyDownPressed, false);
        m_intervalWorks[IntervalWorkMovingBlockDown].intervalSecond = global::Speeds[m_currentSpeed];
        m_grid.AbsorbBlocks(*m_currentBlock);
        m_score += m_grid.CheckClearRow();

        m_currentBlock.reset(GetRandomBlock().release());
        MoveBlockCenter();
        if (m_grid.IsCollided(*m_currentBlock)) {
            NotifySignal(SignalStop, true);
            fmt::print("Game Over. Score: {}\n", m_score);
        }
    }
}

std::unique_ptr<Block> Game::GetRandomBlock()
{
    static std::random_device rd;
    static std::vector<std::function<Block*()>> blockAllocator = {
        [&]() { return new BlockI(); }, [&]() { return new BlockJ(); }, [&]() { return new BlockL(); },
        [&]() { return new BlockO(); }, [&]() { return new BlockS(); }, [&]() { return new BlockT(); },
        [&]() { return new BlockZ(); },
    };
    return std::unique_ptr<Block>(blockAllocator[rd() % blockAllocator.size()]());
}

void Game::Calibrate()
{
    while (true) {
        auto outOfBounds = m_grid.IsOutOfBounds(*m_currentBlock);
        if (outOfBounds == OutOfBoundsNone) {
            break;
        }
        switch (outOfBounds) {
            case OutOfBoundsLeft:
                m_currentBlock->Move(1, 0);
                break;
            case OutOfBoundsRight:
                m_currentBlock->Move(-1, 0);
                break;
            case OutOfBoundsTop:
                m_currentBlock->Move(0, -1);
                break;
            case OutOfBoundsBottom:
                m_currentBlock->Move(0, 1);
                break;
            default:
                break;
        }
    }
}

void Game::Worker()
{
    bool stop = false;
    decltype(m_signals) signalsCopy;
    while (!stop) {
        {
            std::unique_lock<std::mutex> lock(m_signalMutex);
            m_cvSignal.wait(lock, [&]() {
                return std::any_of(m_signals.begin(), m_signals.end(), [](auto&& signal) { return signal.second; });
            });
            signalsCopy = m_signals;
        }

        for (auto&& signal : signalsCopy) {
            if (signal.second) {
                switch (signal.first) {
                    case SignalStop:
                        stop = true;
                        break;
                    case SignalKeyDownPressed: {
                        m_intervalWorks[IntervalWorkMovingBlockDown].intervalSecond =
                            global::Speeds[SpeedMoveBlockDown];
                        break;
                    }
                }
            }
        }
    }
}

void Game::NotifySignal(SignalType signal, bool value)
{
    std::unique_lock<std::mutex> lock(m_signalMutex);
    m_signals[signal] = value;
    lock.unlock();
    m_cvSignal.notify_one();
}
