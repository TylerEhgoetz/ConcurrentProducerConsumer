#ifndef CONSUMER_H
#define CONSUMER_H

#include "ThreadSafeQueue.h"
#include <atomic>
#include <chrono>
#include <iostream>
#include <thread>

extern std::atomic<bool> g_done;

void consumer(ThreadSafeQueue<double>& priceQueue)
{
    while (!g_done.load())
    {
        double price = priceQueue.pop();
        std::cout << "Consumed: " << price << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(500)
        );   // Simulate work
    }
}

#endif   // CONSUMER_H
