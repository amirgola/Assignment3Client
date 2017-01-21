//
// Created by Stephanie Schustermann on 17/01/2017.
//

#ifndef BOOST_ECHO_CLIENT_SOCKETTASK_H
#define BOOST_ECHO_CLIENT_SOCKETTASK_H
#include "Protocol.h"
#include <boost/thread.hpp>

class SocketTask {
private:
    Protocol* _protocol;
public:
    SocketTask(Protocol* protocol);
    void operator()();
};


#endif //BOOST_ECHO_CLIENT_SOCKETTASK_H
