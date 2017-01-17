//
// Created by Stephanie Schustermann on 17/01/2017.
//

#ifndef BOOST_ECHO_CLIENT_KEYBOARDTASK_H
#define BOOST_ECHO_CLIENT_KEYBOARDTASK_H
#include "concurrent_queue.h"
#include "./packets/Packet.h"

class KeyboardTask {
private:
    int* _pendingTasks;
    concurrent_queue<Packet>* _outgoingMessages;
    concurrent_queue<Packet>* _incomingMessages;
public:
    KeyboardTask(int* pendingTasks, concurrent_queue<Packet>* outgoingMessages, concurrent_queue<Packet>* incomingMessages);
    void operator()();
};

#endif //BOOST_ECHO_CLIENT_KEYBOARDTASK_H
