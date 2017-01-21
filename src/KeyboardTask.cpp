//
// Created by Stephanie Schustermann on 17/01/2017.
//
#include <stdlib.h>
#include "../include/KeyboardTask.h"
#include <string>
#include <iostream>
#include <boost/thread.hpp>
#include "../include/Packet.h"
#include "./../include/Protocol.h"
#include "./../include/enums.h"
#include "../include/RRQpacket.h"
#include "../include/WRQpacket.h"
#include "../include/DATApacket.h"
#include "../include/ACKpacket.h"
#include "../include/ERRORpacket.h"
#include "../include/DISCpacket.h"
#include "../include/BCASTpacket.h"
#include "../include/DELRQpacket.h"
#include "../include/LOGRQpacket.h"
#include "../include/DIRQpacket.h"

KeyboardTask::KeyboardTask(Protocol* protocol) : _protocol(protocol){}

void KeyboardTask::operator()(){
    while(enumNamespace::g_status != enumNamespace::PacketType::DISCONNECTED){ //while connected? use lock?
        // get input
        const short bufsize = 512;
        char buf[bufsize];
        std::cin.getline(buf, bufsize);
        std::string line(buf);

        Packet* sendPacket = keyboardParsing(buf);
        MessageEncoderDecoder encDec = MessageEncoderDecoder();
        std::vector<char> encodedMessage = encDec.encode(sendPacket);
        std::string toSend(encodedMessage.begin(), encodedMessage.end());

        if(!_protocol->getConnectionHandler()->sendBytes(toSend.c_str(),toSend.length())){
            enumNamespace::g_status = enumNamespace::PacketType::DISCONNECTED;
        }

        delete sendPacket;
    }

    boost::this_thread::yield(); //Gives up the remainder of the current thread's time slice, to allow other threads to run.
}

Packet* KeyboardTask::keyboardParsing (std::string str) {
    std::size_t found = str.find_first_of(' ');
    std::string fileName = str.substr(static_cast<int>(found)+1);
    std::string command = str.substr(0, static_cast<int>(found));

    if(command == "DIRQ") {
        enumNamespace::g_status = enumNamespace::PacketType::DIRQ;
        return new DIRQpacket();
    }
    if(command =="DELRQ") {
        enumNamespace::g_status = enumNamespace::PacketType::DELRQ;
        return new DELRQpacket(fileName);
    }
    if(command == "RRQ") {
        enumNamespace::g_fileNameString = fileName;
        enumNamespace::g_status = enumNamespace::PacketType::RRQ;
        return new RRQpacket(fileName);
    }
    if(command == "WRQ") {
        enumNamespace::g_fileNameString = fileName;
        enumNamespace::g_status = enumNamespace::PacketType::WRQ;
        return new WRQpacket(fileName);
    }
    if(command == "LOGRQ") {
        enumNamespace::g_status = enumNamespace::PacketType::LOGRQ;
        return new LOGRQpacket(fileName);
    }
    if(command == "DISC") {
        enumNamespace::g_status = enumNamespace::PacketType::DISC;
        return new DISCpacket();
    }

    return new ERRORpacket(0, "Incorrect command");
}