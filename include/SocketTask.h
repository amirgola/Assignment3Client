//
// Created by Stephanie Schustermann on 17/01/2017.
//

#ifndef BOOST_ECHO_CLIENT_SOCKETTASK_H
#define BOOST_ECHO_CLIENT_SOCKETTASK_H
#include "Protocol.h"
#include <boost/thread.hpp>

class SocketTask {
private:
    int* _pendingTasks;
    boost::mutex * _mutex;
    Protocol* _protocol;
public:
    SocketTask(int* pendingTasks, boost::mutex* mutex, Protocol* protocol);
    void operator()();
};


#endif //BOOST_ECHO_CLIENT_SOCKETTASK_H
