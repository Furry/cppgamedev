#include "ticker.h";
#include <iostream>

Ticker::Ticker(std::function<void()> func, std::chrono::milliseconds interval, std::shared_ptr<void> dependency)
    : func_(func), interval_(interval), dependency_(dependency), running_(false) {
}

Ticker::~Ticker() {
    stop();
}

void Ticker::start() {
    if (running_) return;

    running_ = true;
    thread_ = std::thread([this]() {
        while (running_ && !dependency_.expired()) {
            std::this_thread::sleep_for(interval_);
            if (running_ && !dependency_.expired()) {

                func_();
            }
        }
    });
}

void Ticker::stop() {
    if (!running_) return;

    running_ = false;
    if (thread_.joinable()) {
        thread_.join();
    }
}
