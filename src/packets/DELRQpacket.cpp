#include "./../../include/packets/DELRQpacket.h"
#include "./../../include/packets/Packet.h"
//
// Created by Medhopz on 1/16/2017.
//

DELRQpacket::DELRQpacket(std::string fileName):Packet::Packet(8) {
    fileName_ = fileName;
}

std::string DELRQpacket::getFileName() {
    return fileName_;
}
