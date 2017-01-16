#include "./../include/DATApacket.h"

//
// Created by Medhopz on 1/16/2017.
//

DATApacket::DATApacket(short packetSize, short blockNumber, vector<char> data) {
    packetSize_ = packetSize;
    blockNumber_ = blockNumber;
    data_ = data;
}

vector<char> DATApacket::getData() {
    return data_;
}

short DATApacket::getBlockNumber() {
    return blockNumber_;
}
short DATApacket::getPacketSize() {
    return packetSize_;
}
