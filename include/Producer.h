#ifndef PRODUCER_H
#define PRODUCER_H

#include "Random.h"
#include "ThreadSafeQueue.h"
#include <chrono>
#include <iostream>
#include <thread>

void producer(ThreadSafeQueue<double>& priceQueue)
{
    while (true)
    {
        // Generate a random price
        double price = Random::get(0.0, 10000.0);
        priceQueue.push(price);
        std::cout << "Produced: " << price << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(300)
        );   // Simulate work
    }
}

#endif   // PRODUCER_H
