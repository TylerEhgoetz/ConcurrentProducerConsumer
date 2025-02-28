#ifndef PRODUCER_H
#define PRODUCER_H

#include "ThreadSafeQueue.h"
#include <atomic>
#include <chrono>
#include <iostream>
#include <random>
#include <thread>

extern std::atomic<bool> g_done;

void producer(ThreadSafeQueue<double>& priceQueue)
{
    std::random_device               rd;
    std::mt19937                     gen(rd());
    std::uniform_real_distribution<> Random(0.0, 10000.0);
    while (!g_done.load())
    {
        // Generate a random price
        double price = Random(gen);
        priceQueue.push(price);
        std::cout << "Produced: " << price << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(300)
        );   // Simulate work
    }
}

#endif   // PRODUCER_H
