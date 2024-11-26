#pragma once

#include <chrono>
#include <functional>
#include <future>
#include <thread>

template <class _Rep, class _Period>
std::future<void> TimerAsync(std::chrono::duration<_Rep, _Period> duration, std::function<void()> callback)
{
    return std::async(std::launch::async, [&]() {
        std::this_thread::sleep_for(duration);
        callback();
    });
}
