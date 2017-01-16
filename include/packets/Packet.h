#ifndef ACKPACKET_H_
#define ACKPACKET_H_

class Packet{
private:
    short opCode_;
    string msgType;
public:
    Packet();
    short getOpCode();
    string getMsgType();
    virtual ~Packet();
};