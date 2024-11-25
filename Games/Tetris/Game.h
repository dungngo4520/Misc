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
    Grid m_Grid;
    std::unique_ptr<Block> m_CurrentBlock;
    SpeedType m_CurrentSpeed;
    unsigned int m_Score;
    std::thread m_Worker;
    std::condition_variable m_CV;
    std::mutex m_SignalMutex;
    std::map<SignalType, bool> m_Signals;
    std::map<IntervalWorkType, IntervalWork> m_IntervalWorks;

private:
    std::unique_ptr<Block> GetRandomBlock();
    void MoveBlockCenter();
    void MoveBlockLeft();
    void MoveBlockRight();
    void MoveBlockDown();
    void Calibrate();
    void Worker();
    void NotifySignal(SignalType signal, bool value);
};

#endif  // GAME_H
