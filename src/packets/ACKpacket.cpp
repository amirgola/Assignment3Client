#include "./../../include/packets/ACKpacket.h"

//
// Created by Medhopz on 1/16/2017.
//

ACKpacket::ACKpacket(short i) {
    blockNumber_ = i;
}

short ACKpacket::getBlockNumber() {
    return blockNumber_;
}

