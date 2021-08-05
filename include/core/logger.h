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

namespace smol
{
    /**
     * @brief main logger class, controls fetching new messages and reading them and pushing them to sinks
     */
    class logger
    {
    private:
        /**
         * @brief smol::singleton of type logger_queue
         */
        smol::singleton<logger_queue> queue_;
        /**
         * @brief smol::singleton of type logger_reader
         */
        smol::singleton<logger_reader> reader_;

        /**
         * @brief Template private member function used to push new messages to
         * @tparam Args variadic template parameters
         * @param _prefix prefix used to distinguish information type
         * @param _format format string, refer to smol::format for example usage
         * @param _args argument pack
         */
        template<class ...Args>
        void put(std::string const& _prefix, std::string _format, Args&& ... _args)
        {
            queue_->put_message(_prefix + (std::string) smol::format(std::move(_format), std::forward<Args>(_args)...));
        }

    public:
        /**
         * @brief Default constructor
         * @details initializes smol::singleton logger_queue and logger_reader and starts logger_reader thread
         */
        logger();

        /**
         * @brief default destructor
         * @details terminates reader thread and destroys objects held by smol::singleton
         */
        ~logger();

        /**
         * @brief Push INFO message to logger
         * @tparam Args variadic template parameters
         * @param _format format string, refer to smol::format for example usage
         * @param _args argument pack
         */
        template<class ... Args>
        void info(std::string _format, Args&& ... _args)
        {
            this->put(settings::info_prefix, std::move(_format), std::forward<Args>(_args)...);
        }

        /**
         * @brief Push ERROR message to logger
         * @tparam Args variadic template parameters
         * @param _format format string, refer to smol::format for example usage
         * @param _args argument pack
         */
        template<class ... Args>
        void error(std::string _format, Args&& ... _args)
        {
            this->put(settings::error_prefix, std::move(_format), std::forward<Args>(_args)...);
        }

        /**
         * @brief Push FATAL message to logger
         * @tparam Args variadic template parameters
         * @param _format format string, refer to smol::format for example usage
         * @param _args argument pack
         */
        template<class ... Args>
        void fatal(std::string _format, Args&& ... _args)
        {
            this->put(settings::fatal_prefix, std::move(_format), std::forward<Args>(_args)...);
        }

        /**
         * @brief Push WARNING message to logger
         * @tparam Args variadic template parameters
         * @param _format format string, refer to smol::format for example usage
         * @param _args argument pack
         */
        template<class ... Args>
        void warning(std::string _format, Args&& ... _args)
        {
            this->put(settings::warning_prefix, std::move(_format), std::forward<Args>(_args)...);
        }

        /**
         * @brief Push RAW message to logger (no prefix)
         * @tparam Args variadic template parameters
         * @param _format format string, refer to smol::format for example usage
         * @param _args argument pack
         */
        template<class ... Args>
        void raw(std::string _format, Args&& ... _args)
        {
            this->put(std::string(), std::move(_format), std::forward<Args>(_args)...);
        }

        /**
         * @brief Bind target std::ostream object to logger
         * @param _name unique character string representing target sink
         * @param _os reference to target std::ostream based object
         */
        void bind_sink(std::string _name, std::ostream& _os);

        /**
         * @brief Unbind target sink
         * @param _name unique character string representing target sink
         */
        void unbind_sink(std::string const& _name);
    };
}

#endif //SMOL_LOGGER_LOGGER_H
