#pragma once

#include <chrono>
#include <thread>

namespace x {

template <class Delta = float>
class FrameTimer {
public:
    explicit FrameTimer(int fps)
        : _frameDuration(std::chrono::duration_cast<Clock::duration>(
            std::chrono::duration<double>{1.0 / fps}))
        , _delta(static_cast<Delta>(1.0 / fps))
    { }

    Delta delta() const
    {
        return _delta;
    }

    int operator()()
    {
        auto currentFrame = (Clock::now() - _start) / _frameDuration;
        int frameDelta = static_cast<int>(currentFrame - _framesPassed);
        _framesPassed = currentFrame;
        return frameDelta;
    }

    void relax() const
    {
        std::this_thread::sleep_until(
            _start + _frameDuration * (_framesPassed + 1));
    }

    void reset()
    {
        _start = Clock::now();
        _framesPassed = 0;
    }

private:
    using Clock = std::chrono::high_resolution_clock;

    Clock::duration _frameDuration;
    Delta _delta = 0;
    Clock::time_point _start = Clock::now();
    size_t _framesPassed = 0;
};

} // namespace