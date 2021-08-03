/**
 *  @author:    Qsionc
 *  @date:      02/08/2021
 *  @file:      logger_queue.cpp
 *  @brief:     
 *  @Copyright: This software is free to use and distribute free of charge.
 */

#include "implementation/logger_queue.h"

using namespace smol;

std::shared_ptr<std::string> logger_queue::get_next() {
    if (empty()) {
        return {nullptr};
    }
    std::unique_lock lock(mutex_);
    auto result = std::make_shared<std::string>(queue_.front());
    queue_.pop_front();
    lock.unlock();
    return result;
}

logger_queue::logger_queue() = default;

logger_queue::~logger_queue() = default;

void logger_queue::put_message(std::string _msg) {
    std::lock_guard lockGuard(mutex_);
    queue_.push_back(std::move(_msg));
}

bool logger_queue::empty() const {
    std::lock_guard lockGuard(mutex_);
    return queue_.empty();
}
