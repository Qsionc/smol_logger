/**
 *  @author:    Qsionc
 *  @date:      02/08/2021
 *  @file:      logger_reader.cpp
 *  @brief:     
 *  @Copyright: This software is free to use and distribute free of charge.
 */

#include "core/logger_reader.h"

using namespace smol;

void logger_reader::reader_thread(logger_queue& _queue) {
    while (!terminate_flag_) {
        auto result = _queue.get_next();
        if (!result) {
            continue;
        }
        std::lock_guard lock(mutex);
        for (auto& it : sink_list_) {
            (*it.second) << (*result);
        }
    }
}


void logger_reader::clear_queue(logger_queue& _queue)
{
    while(!_queue.empty())
    {
        auto result = _queue.get_next();
        std::lock_guard lock(mutex);
        for (auto& it : sink_list_) {
            (*it.second) << (*result);
        }
    }
}

logger_reader::logger_reader() : terminate_flag_(true) {
}

logger_reader::~logger_reader() {
    terminate();
}

void logger_reader::bind_sink(std::string _name, std::ostream* _sink) {
    std::lock_guard lockGuard(mutex);
    sink_list_.emplace(std::move(_name), std::make_unique<basic_sink>(_sink));
}

void logger_reader::run(logger_queue& _queue) {
    if (terminate_flag_) {
        terminate_flag_ = false;
        std::lock_guard lockGuard(mutex);
        jthread_ = smol::jthread(&logger_reader::reader_thread, this, std::ref(_queue));
    }
}

void logger_reader::terminate() {
    terminate_flag_ = true;
    if (jthread_.joinable()) {
        jthread_.join();
    }
}

void logger_reader::unbind_sink(std::string const& _name) {
    if (this->contains(_name)) {
        sink_list_.erase(_name);
    }
}

bool logger_reader::contains(const std::string& _name) const {
    return sink_list_.contains(_name);
}

