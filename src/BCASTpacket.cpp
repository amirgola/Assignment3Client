#include "../include/BCASTpacket.h"
#include "../include/Packet.h"
//
// Created by Medhopz on 1/16/2017.
//

BCASTpacket::BCASTpacket(char delAdd, std::string fileName):Packet::Packet(9) {
    BCASTpacket::filename_ = fileName;
    BCASTpacket::delAdd_ = delAdd;
}

std::string BCASTpacket::getFileName() {
    return filename_;
}

char BCASTpacket::getDelAdd() {
    return delAdd_;
}
