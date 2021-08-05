/**
 *  @author:    Qsionc
 *  @date:      02/08/2021
 *  @file:      jthread.h
 *  @brief:     
 *  @Copyright: This software is free to use and distribute free of charge.
 */

#ifndef SMOL_LOGGER_JTHREAD_H
#define SMOL_LOGGER_JTHREAD_H

#include <thread>

namespace smol
{
    /**
     * @brief Thread wrapper providing automatic joining functionality
     */
    class jthread
    {
    private:
        /**
         * @brief Wrapped thread object
         */
        std::thread thread;
    public:
        /**
         * @brief default constructor
         */
        jthread() = default;

        /**
         * @brief Argument constructor forwarding arguments to std::thread template constructor
         * @tparam Callable Target callable object, that fulfils requirement std::is_invocable_v<Callable, Params...>
         * @tparam Params Variadic template parameter
         * @param _func universal reference to target object of type Callable
         * @param _params argument pack
         */
        template<class Callable, class... Params>
        requires std::is_invocable_v<Callable, Params...>
        explicit jthread(Callable&& _func, Params&& ... _params) :
            thread(std::forward<Callable>(_func),
                   std::forward<Params>(_params)...)
        {
        }

        /**
         * @brief Move constructor
         * @param _rvalue target rvalue reference to be moved from
         */
        jthread(jthread&& _rvalue) noexcept;

        /**
         * @brief Move Assignment operator
         * @param _rvalue target rvalue reference to be moved from
         * @return reference to assigned object
         */
        jthread& operator=(jthread&& _rvalue) noexcept;

        /**
         * @brief Check if current thread is joinable
         * @return true if joinable, false otherwise
         */
        [[nodiscard]] bool joinable() const;

        /**
         * @brief Wait for thread to finish its task and rejoin it with main thread
         */
        void join();

        /**
         * @brief jthread destructor
         */
        ~jthread();
    };
}

#endif //SMOL_LOGGER_JTHREAD_H
