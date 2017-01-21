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

SocketTask::SocketTask(Protocol* protocol) : _protocol(protocol){}

void SocketTask::operator()(){
    while(enumNamespace::g_status != enumNamespace::PacketType::DISCONNECTED){ //while connected? use lock?
        // get bytes
        char bytes[2];

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