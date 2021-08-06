/**
 *  @author:    Qsionc
 *  @date:      03/08/2021
 *  @file:      logger.cpp
 *  @brief:     
 *  @Copyright: This software is free to use and distribute free of charge.
 */

#include "core/logger.h"

smol::logger::logger() {
    reader_.init();
    queue_.init();
    reader_->run(*queue_);
}

smol::logger::~logger() {
    reader_->terminate();
    reader_->clear_queue(*queue_);
    queue_.destroy();
    reader_.destroy();
}

void smol::logger::bind_sink(std::string _name, std::ostream& _os) {
    reader_->bind_sink(std::move(_name), &_os);
}

void smol::logger::unbind_sink(std::string const& _name) {
    reader_->unbind_sink(_name);
}
