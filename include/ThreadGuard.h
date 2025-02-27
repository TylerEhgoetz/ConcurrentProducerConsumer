#ifndef THREADGUARD_H
#define THREADGUARD_H

#include <thread>

class thread_guard
{
    std::thread m_thread;

public:
    explicit thread_guard(std::thread t)
        : m_thread(std::move(t))
    {
        if (!m_thread.joinable())
        {
            throw std::logic_error("No thread");
        }
    }

    ~thread_guard() { m_thread.join(); }
    thread_guard(thread_guard const&)            = delete;
    thread_guard& operator=(thread_guard const&) = delete;
};

#endif   // THREADGUARD_H
