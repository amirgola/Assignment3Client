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
    while(enumNamespace::g_status != enumNamespace::PacketType::DISCONNECTED;){ //while connected? use lock?
        // get bytes

        // We can use one of three options to read data from the server:
        // 1. Read a fixed number of characters
        // 2. Read a line (up to the newline character using the getline() buffered reader
        // 3. Read up to the null character
        char bytes[2];
        //char bytes[], unsigned int bytesToRead
        // Get back an answer: by using the expected number of bytes (len bytes + newline delimiter)
        // We could also use: connectionHandler.getline(answer) and then get the answer without the newline char at the end
        if(!_protocol->getConnectionHandler()->getBytes(bytes, 2)){
            break;
        }
        // decode
        MessageEncoderDecoder encDec = MessageEncoderDecoder();
        short type = encDec.decodePacketType(bytes);
        std::cout << "type " <<type << std::endl;
        char message[1];
        Packet* packet = nullptr;

        while(packet == nullptr) {
            if(!_protocol->getConnectionHandler()->getBytes(message, 1)){
                enumNamespace::g_status = enumNamespace::PacketType::DISCONNECTED;
            }
            packet = encDec.decodeNextByte(message[0]);
        }

        if(packet != nullptr){
            _protocol->process(packet);
        }
    }

    boost::this_thread::yield(); //Gives up the remainder of the current thread's time slice, to allow other threads to run.
}
