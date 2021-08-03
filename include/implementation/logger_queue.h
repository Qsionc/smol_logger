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

namespace smol {
    class logger_queue {
    private:
        mutable std::mutex mutex_;
        std::deque<std::string> queue_;
    public:
        logger_queue();

        ~logger_queue();

        void put_message(std::string _msg);

        [[nodiscard]] bool empty() const;

        std::shared_ptr<std::string> get_next();
    };
}

#endif //SMOL_LOGGER_LOGGER_QUEUE_H
