//
// Created by Stephanie Schustermann on 17/01/2017.
//

#include "../include/concurrent_queue.h"
#include <queue>
#include <boost/thread.hpp>
#include "./../include/packets/Packet.h"
template<>
void concurrent_queue<Packet>::push(Packet const& data) {
    boost::mutex::scoped_lock lock(the_mutex);
    the_queue.push(data);
    lock.unlock();
    the_condition_variable.notify_one();
}
template<>
bool concurrent_queue<Packet>::empty() const {
    boost::mutex::scoped_lock lock(the_mutex);
    return the_queue.empty();
}

template<>
bool concurrent_queue<Packet>::try_pop(Packet& popped_value) {
    boost::mutex::scoped_lock lock(the_mutex);
    if (the_queue.empty()) {
        return false;
    }

    popped_value = the_queue.front();
    the_queue.pop();
    return true;
}

template<>
void concurrent_queue<Packet>::wait_and_pop(Packet& popped_value) {
    boost::mutex::scoped_lock lock(the_mutex);
    while (the_queue.empty()) {
        the_condition_variable.wait(lock);
    }

    popped_value = the_queue.front();
    the_queue.pop();
}
