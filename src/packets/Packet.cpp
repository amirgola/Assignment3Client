#include "./../../include/packets/Packet.h"

short Packet::getOpCode(){
    return opCode_;
}

std::string Packet::getMsgType(){
    return msgType;
}

Packet::Packet(short opCode):opCode_(opCode){}

Packet::Packet(const Packet& other):opCode_(other.opCode_), msgType(other.msgType){}

Packet::~Packet() {}