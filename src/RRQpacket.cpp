#include "../include/RRQpacket.h"
#include "../include/Packet.h"
//
// Created by Medhopz on 1/16/2017.
//

RRQpacket::RRQpacket(std::string fileName):Packet::Packet(1), fileName_(fileName) {
}

std::string RRQpacket::getFileName() {
    return fileName_;
}
