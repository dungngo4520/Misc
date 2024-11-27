#pragma once

#include <chrono>
#include <functional>
#include <future>
#include <thread>

namespace utils {
    namespace syncing {
        template <class _Rep, class _Period>
        std::future<void> TimerAsync(std::chrono::duration<_Rep, _Period> duration, std::function<void()> callback)
        {
            return std::async(std::launch::async, [duration, callback]() {
                std::this_thread::sleep_for(duration);
                callback();
            });
        }
    }  // namespace syncing
}  // namespace utils
