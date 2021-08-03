/**
 *  @author:    Qsionc
 *  @date:      02/08/2021
 *  @file:      basic_sink.h
 *  @brief:     
 *  @Copyright: This software is free to use and distribute free of charge.
 */

#ifndef SMOL_LOGGER_BASIC_SINK_H
#define SMOL_LOGGER_BASIC_SINK_H

#include <ostream>

namespace smol {
    class basic_sink {
    private:
        std::ostream* const ostream_;
    public:
        explicit basic_sink(std::ostream* _ptr);

        ~basic_sink();

        template<class T>
        basic_sink& operator<<(T& _object) {
            (*ostream_) << _object;
            return *this;
        }

        template<class T>
        basic_sink& operator<<(T&& _object) {
            (*ostream_) << _object;
            return *this;
        }
    };
}


#endif //SMOL_LOGGER_BASIC_SINK_H
