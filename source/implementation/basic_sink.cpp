/**
 *  @author:    Qsionc
 *  @date:      02/08/2021
 *  @file:      basic_sink.cpp
 *  @brief:     
 *  @Copyright: This software is free to use and distribute free of charge.
 */


#include "implementation/basic_sink.h"

smol::basic_sink::basic_sink(std::ostream* _ptr) :
        ostream_(_ptr) {
}

smol::basic_sink::~basic_sink() = default;
