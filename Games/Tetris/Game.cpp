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
    m_Grid(20, 10),
    m_CurrentBlock(GetRandomBlock()),
    m_CurrentSpeed(SpeedNormal),
    m_Score(0),
    m_Worker([&]() { Worker(); }),
    m_Signals({
        { SignalStop, false },
        { SignalKeyDownPressed, false },
    }),
    m_IntervalWorks({ { IntervalWorkMovingBlockDown,
                        { global::Speeds.at(m_CurrentSpeed), [&]() { MoveBlockDown(); } } } })
{
    SetTargetFPS(60);
    MoveBlockCenter();
}

Game::~Game()
{
    NotifySignal(SignalStop, true);
    m_Worker.join();
}

void Game::Draw()
{
    m_Grid.Draw();
    m_CurrentBlock->Draw();
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
            m_CurrentBlock->Rotate();
            Calibrate();
            break;
    }
}

void Game::Loop()
{
    double lastTime = GetTime();
    auto CheckWork = [&]() {
        double currentTime = GetTime();
        for (auto&& work : m_IntervalWorks) {
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

void Game::MoveBlockCenter() { m_CurrentBlock->Move((m_Grid.GetWidth() - m_CurrentBlock->GetWidth()) / 2, 0); }

void Game::MoveBlockLeft()
{
    m_CurrentBlock->Move(-1, 0);
    Calibrate();
    if (m_Grid.IsCollided(*m_CurrentBlock)) {
        m_CurrentBlock->Move(1, 0);
    }
}

void Game::MoveBlockRight()
{
    m_CurrentBlock->Move(1, 0);
    Calibrate();
    if (m_Grid.IsCollided(*m_CurrentBlock)) {
        m_CurrentBlock->Move(-1, 0);
    }
}

void Game::MoveBlockDown()
{
    m_CurrentBlock->Move(0, 1);

    if (m_Grid.IsCollided(*m_CurrentBlock)) {
        m_CurrentBlock->Move(0, -1);
        NotifySignal(SignalKeyDownPressed, false);
        m_IntervalWorks[IntervalWorkMovingBlockDown].intervalSecond = global::Speeds.at(m_CurrentSpeed);
        m_Grid.AbsorbBlocks(*m_CurrentBlock);
        m_Score += m_Grid.CheckClearRow();

        m_CurrentBlock.reset(GetRandomBlock().release());
        MoveBlockCenter();
        if (m_Grid.IsCollided(*m_CurrentBlock)) {
            NotifySignal(SignalStop, true);
            fmt::print("Game Over. Score: {}\n", m_Score);
        }
    }
}

void Game::Calibrate()
{
    while (true) {
        auto outOfBounds = m_Grid.IsOutOfBounds(*m_CurrentBlock);
        if (outOfBounds == OutOfBoundsNone) {
            break;
        }
        switch (outOfBounds) {
            case OutOfBoundsLeft:
                m_CurrentBlock->Move(1, 0);
                break;
            case OutOfBoundsRight:
                m_CurrentBlock->Move(-1, 0);
                break;
            case OutOfBoundsTop:
                m_CurrentBlock->Move(0, -1);
                break;
            case OutOfBoundsBottom:
                m_CurrentBlock->Move(0, 1);
                break;
            default:
                break;
        }
    }
}

void Game::Worker()
{
    bool stop = false;
    decltype(m_Signals) signalsCopy;
    while (!stop) {
        {
            std::unique_lock<std::mutex> lock(m_SignalMutex);
            m_CV.wait(lock, [&]() {
                return std::any_of(m_Signals.begin(), m_Signals.end(), [](auto&& signal) { return signal.second; });
            });
            signalsCopy = m_Signals;
        }

        for (auto&& signal : signalsCopy) {
            if (signal.second) {
                switch (signal.first) {
                    case SignalStop:
                        stop = true;
                        break;
                    case SignalKeyDownPressed: {
                        m_IntervalWorks[IntervalWorkMovingBlockDown].intervalSecond =
                            global::Speeds.at(SpeedMoveBlockDown);
                        break;
                    }
                }
            }
        }
    }
}

void Game::NotifySignal(SignalType signal, bool value)
{
    std::unique_lock<std::mutex> lock(m_SignalMutex);
    m_Signals[signal] = value;
    lock.unlock();
    m_CV.notify_one();
}
