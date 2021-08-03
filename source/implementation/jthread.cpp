/**
 *  @author:    Qsionc
 *  @date:      02/08/2021
 *  @file:      jthread.cpp
 *  @brief:     
 *  @Copyright: This software is free to use and distribute free of charge.
 */

#include "implementation/jthread.h"

using namespace smol;

smol::jthread::jthread(jthread&& _rvalue) noexcept:
        thread(std::move(_rvalue.thread)) {}

jthread& smol::jthread::operator=(jthread&& _rvalue) noexcept {
    thread = std::move(_rvalue.thread);
    return *this;
}

smol::jthread::~jthread() {
    if (this->joinable()) {
        this->join();
    }
}

bool jthread::joinable() const {
    return thread.joinable();
}

void jthread::join() {
    thread.join();
}
