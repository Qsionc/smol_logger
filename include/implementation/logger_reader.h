/**
 *  @author:    Qsionc
 *  @date:      02/08/2021
 *  @file:      logger_reader.h
 *  @brief:     
 *  @Copyright: This software is free to use and distribute free of charge.
 */

#ifndef SMOL_LOGGER_LOGGER_READER_H
#define SMOL_LOGGER_LOGGER_READER_H

#include <unordered_map>
#include <mutex>
#include <singleton.h>
#include "jthread.h"
#include "basic_sink.h"
#include "logger_queue.h"

namespace smol {
    class logger_reader {
    private:
        std::atomic_bool terminate_flag;
        jthread jthread_;
        std::mutex mutex;
        singleton<logger_queue> queue_;
        std::unordered_map<std::string, std::unique_ptr<basic_sink>> sink_list_;

        void reader_thread();

    public:
        logger_reader();

        ~logger_reader();

        void bind_sink(std::string _key, std::ostream* _sink);

        void run();

        void terminate();
    };
}


#endif //SMOL_LOGGER_LOGGER_READER_H
