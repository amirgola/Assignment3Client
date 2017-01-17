//
// Created by Stephanie Schustermann on 17/01/2017.
//

#ifndef BOOST_ECHO_CLIENT_KEYBOARDTASK_H
#define BOOST_ECHO_CLIENT_KEYBOARDTASK_H
#include "Protocol.h"
#include <boost/thread.hpp>

class KeyboardTask {
private:
    int* _pendingTasks;
    boost::mutex * _mutex;
    Protocol* _protocol;
public:
    KeyboardTask(int* pendingTasks, boost::mutex* mutex, Protocol* protocol);
    void operator()();
    Packet keyboardParsing (std::string str);
};

#endif //BOOST_ECHO_CLIENT_KEYBOARDTASK_H
