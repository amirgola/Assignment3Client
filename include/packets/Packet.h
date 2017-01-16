#ifndef PACKET_H_
#define PACKET_H_

#include <string>
#include <sstream>
#include <iostream>

class Packet{
private:
    short opCode_;
    std::string msgType;
public:
    Packet();
    Packet(const Packet& other);
    short getOpCode();
    std::string getMsgType();
    virtual ~Packet();
};

#endif