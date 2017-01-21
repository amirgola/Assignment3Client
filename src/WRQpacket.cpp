#include "../include/WRQpacket.h"
#include "../include/Packet.h"
//
// Created by Medhopz on 1/16/2017.
//

WRQpacket::WRQpacket(std::string fileName):Packet::Packet(2) {
    fileName_ = fileName;
}

std::string WRQpacket::getFileName() {
    return fileName_;
}
