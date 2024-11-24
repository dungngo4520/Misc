#ifndef GAME_H
#define GAME_H

#include "Block.h"
#include "Common.h"
#include "grid.h"
#include <condition_variable>
#include <functional>
#include <memory>
#include <mutex>
#include <raylib.h>
#include <thread>

class Game {
    enum SignalType { SignalStop, SignalKeyDownPressed };
    enum IntervalWorkType { IntervalWorkMovingBlockDown };

    struct IntervalWork {
        double intervalSecond;
        std::function<void()> work;
    };

public:
    Game(int FPS);
    ~Game();

    void Draw();
    void HandleInput();
    void Loop();

private:
    void MoveBlockCenter();
    void MoveBlockLeft();
    void MoveBlockRight();
    void MoveBlockDown();

    std::unique_ptr<Block> GetRandomBlock();
    void Calibrate();

    Grid m_grid;
    std::unique_ptr<Block> m_currentBlock;
    SpeedType m_currentSpeed;

    int m_score;

    std::thread m_worker;

    std::condition_variable m_cvSignal;
    std::mutex m_signalMutex;
    std::map<SignalType, bool> m_signals;

    std::map<IntervalWorkType, IntervalWork> m_intervalWorks;

    void Worker();
    void NotifySignal(SignalType signal, bool value);
};

#endif  // GAME_H
