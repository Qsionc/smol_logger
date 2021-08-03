/**
 *  @author:    Qsionc
 *  @date:      02/08/2021
 *  @file:      logger_reader.cpp
 *  @brief:     
 *  @Copyright: This software is free to use and distribute free of charge.
 */

#include "implementation/logger_reader.h"

using namespace smol;

void logger_reader::reader_thread() {
    while (!terminate_flag) {
        auto result = queue_->get_next();
        if (!result) {
            continue;
        }
        std::unique_lock lock(mutex);
        for (auto& it : sink_list_) {
            (*it.second) << (*result);
        }
    }
}

logger_reader::logger_reader() : terminate_flag(false) {
    if (!queue_.initialized()) {
        queue_.init();
    }
}

logger_reader::~logger_reader() {
    terminate_flag = false;
}

void logger_reader::bind_sink(std::string _key, std::ostream* _sink) {
    std::lock_guard lockGuard(mutex);
    sink_list_.emplace(std::move(_key), std::make_unique<basic_sink>(_sink));
}

void logger_reader::run() {
    std::lock_guard lockGuard(mutex);
    terminate_flag = false;
    jthread_ = smol::jthread(&logger_reader::reader_thread, this);
}

void logger_reader::terminate() {
    terminate_flag = false;
}
