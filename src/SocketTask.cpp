//
// Created by Stephanie Schustermann on 17/01/2017.
//

#include "../include/SocketTask.h"
#include <iostream>
#include <boost/thread.hpp>
#include "./../include/concurrent_queue.h"
#include "../include/packets/Packet.h"
#include "./../include/connectionHandler.h"

SocketTask::SocketTask(int* pendingTasks, concurrent_queue<Packet>* outgoingMessages,
                       concurrent_queue<Packet>* incomingMessages, boost::mutex* mutex,
                       ConnectionHandler* connectionHandler)
        : _pendingTasks(pendingTasks), _outgoingMessages(outgoingMessages), _incomingMessages(incomingMessages),
          _mutex(mutex), _connectionHandler(connectionHandler){}

void SocketTask::operator()(){
    while(true){ //while connected? use lock?
        // get bytes

        // We can use one of three options to read data from the server:
        // 1. Read a fixed number of characters
        // 2. Read a line (up to the newline character using the getline() buffered reader
        // 3. Read up to the null character
        std::string answer;
        // Get back an answer: by using the expected number of bytes (len bytes + newline delimiter)
        // We could also use: connectionHandler.getline(answer) and then get the answer without the newline char at the end
        if (!_connectionHandler->getLine(answer)) {
            std::cout << "Disconnected. Exiting...\n" << std::endl;
            break;
        }

        int len=answer.length();
        // A C string must end with a 0 char delimiter.  When we filled the answer buffer from the socket
        // we filled up to the \n char - we must make sure now that a 0 char is also present. So we truncate last character.
        answer.resize(len-1);

        // convert to packet
        // put the packet to incoming messages (using lock)

        // show incoming message
        std::cout << "Reply: " << answer << " " << len << " bytes " << std::endl << std::endl;
        if (answer == "bye") {
            std::cout << "Exiting...\n" << std::endl;
            break;
        }
    }

    boost::this_thread::yield(); //Gives up the remainder of the current thread's time slice, to allow other threads to run.
}
