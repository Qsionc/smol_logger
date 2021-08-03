/**
 *  @author:    Qsionc
 *  @date:      03/08/2021
 *  @file:      logger.h
 *  @brief:     
 *  @Copyright: This software is free to use and distribute free of charge.
 */

#ifndef SMOL_LOGGER_LOGGER_H
#define SMOL_LOGGER_LOGGER_H

#include <string>
#include <ostream>
#include <format.h>
#include <singleton.h>
#include "logger_queue.h"
#include "logger_reader.h"
#include "settings/logger_settings.h"

namespace smol {
    class logger {
    private:
        smol::singleton<logger_queue> queue_;
        smol::singleton<logger_reader> reader_;

        template<class ...Args>
        void put(std::string const& _prefix, std::string _format, Args&& ... _args) {
            queue_->put_message(_prefix + (std::string)smol::format(std::move(_format), std::forward<Args>(_args)...));
        }

    public:
        logger();

        ~logger();

        template<class ... Args>
        void info(std::string _format, Args&& ... _args) {
            this->put(settings::info_prefix, std::move(_format), std::forward<Args>(_args)...);
        }

        template<class ... Args>
        void error(std::string _format, Args&& ... _args) {
            this->put(settings::error_prefix, std::move(_format), std::forward<Args>(_args)...);
        }

        template<class ... Args>
        void fatal(std::string _format, Args&& ... _args) {
            this->put(settings::fatal_prefix, std::move(_format), std::forward<Args>(_args)...);
        }

        template<class ... Args>
        void warning(std::string _format, Args&& ... _args) {
            this->put(settings::warning_prefix, std::move(_format), std::forward<Args>(_args)...);
        }

        template<class ... Args>
        void raw(std::string _format, Args&& ... _args) {
            this->put(std::string(), std::move(_format), std::forward<Args>(_args)...);
        }

        void bind_sink(std::string _name, std::ostream& _os);

        void unbind_sink(std::string const& _name);
    };
}


#endif //SMOL_LOGGER_LOGGER_H
