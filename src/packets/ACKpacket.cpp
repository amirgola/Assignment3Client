#include "./../../include/packets/ACKpacket.h"
#include "./../../include/packets/Packet.h"
//
// Created by Medhopz on 1/16/2017.
//

ACKpacket::ACKpacket(short i):Packet::Packet(4) {
    blockNumber_ = i;
}

short ACKpacket::getBlockNumber() {
    return blockNumber_;
}

