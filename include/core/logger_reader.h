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
#include "jthread.h"
#include "basic_sink.h"
#include "logger_queue.h"

namespace smol {
    class logger_reader {
    private:
        std::atomic_bool terminate_flag;
        jthread jthread_;
        std::mutex mutex;
        std::unordered_map<std::string, std::unique_ptr<basic_sink>> sink_list_;

        void reader_thread(logger_queue& _queue);

    public:
        logger_reader();

        ~logger_reader();

        void bind_sink(std::string _name, std::ostream* _sink);

        void unbind_sink(std::string const& _name);

        bool contains(std::string const& _name) const;

        void run(logger_queue& _queue);

        void terminate();
    };
}


#endif //SMOL_LOGGER_LOGGER_READER_H
