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

namespace smol
{
    /**
     * @brief Class holding one std::ostream sink
     */
    class basic_sink
    {
    private:
        /**
         * @brief Constant pointer to target std::ostream object with automatic storage duration
         */
        std::ostream* const ostream_;
    public:
        /**
         * @brief Construct new basic_sink with target constant pointer
         * @param _ptr Pointer to target std::ostream based class with automatic storage duration
         */
        explicit basic_sink(std::ostream* _ptr);

        /**
         * @brief Default destructor
         */
        ~basic_sink();

        /**
         * @brief operator<< overload for lvalue references of template type T
         * @tparam T any class that supports std::ostream operator<<
         * @param _object target lvalue object of type T
         * @return reference to smol::basic_sink, for operator chain
         */
        template<class T>
        basic_sink& operator<<(T& _object)
        {
            (*ostream_) << _object;
            return *this;
        }

        /**
         * @brief operator<< overload for rvalue references of template type T
         * @tparam T any class that supports std::ostream operator<<
         * @param _object target rvalue object of type T
         * @return reference to smol::basic_sink, for operator chain
         */
        template<class T>
        basic_sink& operator<<(T&& _object)
        {
            (*ostream_) << _object;
            return *this;
        }
    };
}

#endif //SMOL_LOGGER_BASIC_SINK_H
