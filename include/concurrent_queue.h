//
// Created by Stephanie Schustermann on 17/01/2017.
//

#ifndef BOOST_ECHO_CLIENT_CONCURRENT_QUEUE_H
#define BOOST_ECHO_CLIENT_CONCURRENT_QUEUE_H
#include <queue>
#include <boost/thread.hpp>

template<typename Packet>

class concurrent_queue {
private:
    std::queue<Packet> the_queue;
    mutable boost::mutex the_mutex;
    boost::condition_variable the_condition_variable;
public:
    void push(Packet const& data);
    bool empty() const;
    bool try_pop(Packet& popped_value);
    void wait_and_pop(Packet& popped_value);
};


#endif //BOOST_ECHO_CLIENT_CONCURRENT_QUEUE_H
