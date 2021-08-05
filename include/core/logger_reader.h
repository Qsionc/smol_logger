/**
 *  @author:    Qsionc
 *  @date:      02/08/2021
 *  @file:      logger_reader.h
 *  @brief:     logger_reader class definition header file
 *  @Copyright: This software is free to use and distribute free of charge.
 */

#ifndef SMOL_LOGGER_LOGGER_READER_H
#define SMOL_LOGGER_LOGGER_READER_H

#include <unordered_map>
#include <mutex>
#include "jthread.h"
#include "basic_sink.h"
#include "logger_queue.h"

namespace smol
{
    /**
     * @brief class representing independent thread that pulls data from message queue
     * @details This class created new thread that reads data from target logger_queue passed to thread function upon
     * thread creation
     */
    class logger_reader
    {
    private:
        /**
         * @brief Flag that signals termination of reader_thread
         */
        std::atomic_bool terminate_flag_;
        /**
         * @brief Automatically joining thread.
         */
        jthread jthread_;
        /**
         * @brief Thread-safety measures
         */
        std::mutex mutex;
        /**
         * @brief Container holding unique references to sinks
         */
        std::unordered_map<std::string, std::unique_ptr<basic_sink>> sink_list_;

        /**
         * @brief reader thread main function
         * @param _queue reference to target queue to be read from
         */
        void reader_thread(logger_queue& _queue);

    public:
        /**
         * @brief Default constructor
         */
        logger_reader();

        /**
         * @brief Destructor
         * @details terminates thread upon destruction if it was not terminated
         */
        ~logger_reader();

        /**
         * @brief Bind target std::ostream
         * @param _name unique string identifier, used later for easy unbinding of sinks
         * @param _sink pointer to target std::ostream (of automatic duration object)
         */
        void bind_sink(std::string _name, std::ostream* _sink);

        /**
         * @brief Unbind target sink
         * @param _name target unique identifier
         */
        void unbind_sink(std::string const& _name);

        /**
         * @brief check, if reader's sink list contains target key string
         * @param _name key to be checked
         * @return true if _name is present as key in sink list, false otherwise
         */
        bool contains(std::string const& _name) const;

        /**
         * @brief create new reading thread if there is none running at the moment
         * @param _queue target message queue to be read from
         * @details this method creates thread only once. To create new thread, you need to call
         * smol::logger_reader::terminate() first.
         */
        void run(logger_queue& _queue);

        /**
         * @brief Terminate current thread if there is one running. No effect otherwise.
         */
        void terminate();
    };
}

#endif //SMOL_LOGGER_LOGGER_READER_H
