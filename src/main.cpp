#include "Consumer.h"
#include "Producer.h"
#include "ThreadGuard.h"
#include "ThreadSafeQueue.h"
#include <atomic>
#include <iostream>
#include <thread>

std::atomic<bool> g_done{ false };

int main()
{
    ThreadSafeQueue<double> priceQueue;

    // Create a producer and consumer thread and start them
    // its important that we pass the priceQueue by reference since we want the
    // producer and consumer to share the same queue and we must use std::ref to
    // pass the reference to the thread constructor
    thread_guard producerThread(std::thread(producer, std::ref(priceQueue)));
    thread_guard consumerThread(std::thread(consumer, std::ref(priceQueue)));

    // Wait for 10 seconds
    std::this_thread::sleep_for(std::chrono::seconds(10));
    g_done.store(true);
    priceQueue.notify_all();
    return 0;
}
