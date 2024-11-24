#include "Game.h"

#include <fmt/ostream.h>
#include <fmt/std.h>
#include <raylib.h>

#include <thread>


int main(int argc, char const* argv[])
{
    fmt::print("Start in thread {}\n", std::this_thread::get_id());

    InitWindow(300, 600, "Tetris");
    Game(60).Loop();
    CloseWindow();

    return 0;
}
