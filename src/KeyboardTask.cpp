//
// Created by Stephanie Schustermann on 17/01/2017.
//

#include "../include/KeyboardTask.h"
#include <iostream>
#include <boost/thread.hpp>
#include "../include/packets/Packet.h"
#include "./../include/Protocol.h"
#include "./../include/enums.h"
#include "./../include/packets/RRQpacket.h"
#include "./../include/packets/WRQpacket.h"
#include "./../include/packets/DATApacket.h"
#include "./../include/packets/ACKpacket.h"
#include "./../include/packets/ERRORpacket.h"
#include "./../include/packets/DISCpacket.h"
#include "./../include/packets/BCASTpacket.h"
#include "./../include/packets/DELRQpacket.h"
#include "./../include/packets/LOGRQpacket.h"
#include "./../include/packets/DIRQpacket.h"

KeyboardTask::KeyboardTask(int* pendingTasks, boost::mutex* mutex,
                           Protocol* protocol)
        : _pendingTasks(pendingTasks), _mutex(mutex), _protocol(protocol){}

void KeyboardTask::operator()(){
    while(true){ //while connected? use lock?
        // get input
        const short bufsize = 1024;
        char buf[bufsize];
        std::cin.getline(buf, bufsize);
        std::string line(buf);
        int len=line.length();

        Packet sendPacket = keyboardParsing(line);

        _protocol->process(&sendPacket);


        // connectionHandler.sendLine(line) appends '\n' to the message. Therefor we send len+1 bytes.
        std::cout << "Sent " << len+1 << " bytes to server" << std::endl;
    }

    boost::this_thread::yield(); //Gives up the remainder of the current thread's time slice, to allow other threads to run.
}

//
// Created by Medhopz on 1/17/2017.
//

Packet KeyboardTask::keyboardParsing (std::string str) {
    std::size_t found = str.find_first_of(" ");
    std::string command = str.substr(0, found);
    std::string fileName = str.substr(found);

    if(command == "DIRQ") {
            enumNamespace::g_status = enumNamespace::PacketType::DIRQ;
        return DIRQpacket();
    }
    if(command =="DELRQ") {
        enumNamespace::g_status = enumNamespace::PacketType::DELRQ;
        return DELRQpacket(fileName);
    }
    if(command == "RRQ") {
        enumNamespace::g_fileNameString = fileName;
        enumNamespace::g_status = enumNamespace::PacketType::RRQ;
        return RRQpacket(fileName);
    }
    if(command == "WRQ") {
        enumNamespace::g_fileNameString = fileName;
        enumNamespace::g_status = enumNamespace::PacketType::WRQ;
        return WRQpacket(fileName);
    }
    if(command == "LOGRQ") {
        enumNamespace::g_status = enumNamespace::PacketType::LOGRQ;
        return LOGRQpacket(fileName);
    }
    if(command == "DISC") {
        enumNamespace::g_status = enumNamespace::PacketType::DISC;
        return DISCpacket();
    }

    return ERRORpacket(0, "Incorrect command");
}