//
// Created by Stephanie Schustermann on 17/01/2017.
//

#include "../include/SocketTask.h"
#include <iostream>
#include <boost/thread.hpp>
#include "../include/packets/Packet.h"
#include "./../include/Protocol.h"
#include "./../include/enums.h"
#include "./../include/packets/ERRORpacket.h"

SocketTask::SocketTask(int* pendingTasks, boost::mutex* mutex,
                       Protocol* protocol)
        : _pendingTasks(pendingTasks), _mutex(mutex), _protocol(protocol){}

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
        if(!_protocol->getConnectionHandler()->getLine(answer)){
            break;
        }
        // decode
        MessageEncoderDecoder encDec = MessageEncoderDecoder();
        for(char& c : answer) {
            Packet packet = encDec.decodeNextByte(c);
            if(packet.getOpCode() != enumNamespace::PacketType::ERROR || ((ERRORpacket*)&packet)->getErrCode() != 999){
                _protocol->process(&packet);
            }
        }
    }

    boost::this_thread::yield(); //Gives up the remainder of the current thread's time slice, to allow other threads to run.
}
