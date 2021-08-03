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

namespace smol {
    class jthread {
    private:
        std::thread thread;
    public:
        jthread() = default;

        template<class Callable, class... Params>
        requires std::is_invocable_v<Callable, Params...>
        explicit jthread(Callable&& _func, Params&& ... _params) : thread(std::forward<Callable>(_func),
                                                                          std::forward<Params>(_params)...) {
        }

        jthread(jthread&& _rvalue) noexcept;

        jthread& operator=(jthread&& _rvalue) noexcept;

        [[nodiscard]] bool joinable() const;

        void join();

        ~jthread();
    };
}

#endif //SMOL_LOGGER_JTHREAD_H
