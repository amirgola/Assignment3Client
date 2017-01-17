//
// Created by Stephanie Schustermann on 17/01/2017.
//

#include "../include/KeyboardTask.h"
#include <iostream>
#include <boost/thread.hpp>

KeyboardTask::KeyboardTask(int number) : _id(number) {}

void KeyboardTask::operator()(){
    while(true){ //while connected? use lock?
        // get input
        // convert to packet
        // put the packet to outgoing messages (using lock)
    }

    boost::this_thread::yield(); //Gives up the remainder of the current thread's time slice, to allow other threads to run.
}
