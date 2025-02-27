#ifndef THREADSAFEQUEUE_H
#define THREADSAFEQUEUE_H

#include <condition_variable>
#include <mutex>
#include <queue>

template <typename T>
class ThreadSafeQueue
{
public:
    ThreadSafeQueue()
        : m_queue(), m_mutex(), m_conditionVariable()
    {}
    void push(const T& value)
    {
        std::lock_guard<std::mutex> lock(m_mutex);
        m_queue.push(value);
        m_conditionVariable.notify_one();
    }

    T pop()
    {
        std::unique_lock<std::mutex> lock(m_mutex);
        m_conditionVariable.wait(lock, [this] { return !m_queue.empty(); });
        T value = m_queue.front();
        m_queue.pop();
        return value;
    }

    void notify_all() { m_conditionVariable.notify_all(); }

private:
    std::queue<T>           m_queue;
    mutable std::mutex      m_mutex;
    std::condition_variable m_conditionVariable;
};

#endif   // THREADSAFEQUEUE_H
