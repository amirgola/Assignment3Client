//
// Created by Stephanie Schustermann on 17/01/2017.
//

#include "../include/SocketTask.h"
#include <iostream>
#include <boost/thread.hpp>

SocketTask::SocketTask(int number) : _id(number) {}

void SocketTask::operator()(){
    while(true){ //while connected? use lock?
        // get bytes
        // convert to packet
        // put the packet to incoming messages (using lock)
    }

    boost::this_thread::yield(); //Gives up the remainder of the current thread's time slice, to allow other threads to run.
}
