#ifndef TICKER_H
#define TICKER_H

#include <functional>
#include <thread>
#include <chrono>
#include <atomic>
#include <memory>

class Ticker {
    public:
    Ticker(std::function<void()> func, std::chrono::milliseconds interval, std::shared_ptr<void> dependency);
    ~Ticker();

    void start();
    void stop();

    private:
        std::function<void()> func_;
        std::chrono::milliseconds interval_;
        std::weak_ptr<void> dependency_;
        std::atomic_bool running_;
        std::thread thread_;
};

#endif // TICKER_H
