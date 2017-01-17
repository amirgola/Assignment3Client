//
// Created by Stephanie Schustermann on 17/01/2017.
//

#include "../include/KeyboardTask.h"
#include <iostream>
#include <boost/thread.hpp>
#include "./../include/concurrent_queue.h"
#include "../include/packets/Packet.h"
#include "./../include/connectionHandler.h"

KeyboardTask::KeyboardTask(int* pendingTasks, concurrent_queue<Packet>* outgoingMessages,
                           concurrent_queue<Packet>* incomingMessages, boost::mutex* mutex,
                           ConnectionHandler* connectionHandler)
        : _pendingTasks(pendingTasks), _outgoingMessages(outgoingMessages), _incomingMessages(incomingMessages),
            _mutex(mutex), _connectionHandler(connectionHandler){}

void KeyboardTask::operator()(){
    while(true){ //while connected? use lock?
        // get input
        const short bufsize = 1024;
        char buf[bufsize];
        std::cin.getline(buf, bufsize);
        std::string line(buf);
        int len=line.length();

        //TODO convert to packet

        Packet sendPacket = handleKeyboard::proccess(line);

        // put the packet to outgoing messages (using lock)
        if (!_connectionHandler->sendLine(line)) {
            std::cout << "Disconnected. Exiting...\n" << std::endl;
            break;
        }
        // connectionHandler.sendLine(line) appends '\n' to the message. Therefor we send len+1 bytes.
        std::cout << "Sent " << len+1 << " bytes to server" << std::endl;
    }

    boost::this_thread::yield(); //Gives up the remainder of the current thread's time slice, to allow other threads to run.
}
