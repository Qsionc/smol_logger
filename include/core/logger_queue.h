/**
 *  @author:    Qsionc
 *  @date:      02/08/2021
 *  @file:      logger_queue.h
 *  @brief:     
 *  @Copyright: This software is free to use and distribute free of charge.
 */

#ifndef SMOL_LOGGER_LOGGER_QUEUE_H
#define SMOL_LOGGER_LOGGER_QUEUE_H

#include <deque>
#include <string>
#include <mutex>
#include <memory>

namespace smol
{
    /**
     * @brief Class representing message queue used to push data to logger
     */
    class logger_queue
    {
    private:
        /**
         * @brief Thread-safety measures
         */
        mutable std::mutex mutex_;
        /**
         * @brief container holding logger formatted messages
         */
        std::deque<std::string> queue_;
    public:
        /**
         * @brief Default constructor
         */
        logger_queue();

        /**
         * @brief Default destructor
         */
        ~logger_queue();

        /**
         * @brief Push message to queue
         * @param _msg target message to be pushed
         */
        void put_message(std::string _msg);

        /**
         * @brief Check, if message queue is empty
         * @return true if empty, false otherwise
         */
        [[nodiscard]] bool empty() const;

        /**
         * @brief get next queued message
         * @return std::shared_ptr owning object that holds next message
         */
        std::shared_ptr<std::string> get_next();
    };
}

#endif //SMOL_LOGGER_LOGGER_QUEUE_H
