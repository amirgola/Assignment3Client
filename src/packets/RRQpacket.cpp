#include "./../../include/packets/RRQpacket.h"

//
// Created by Medhopz on 1/16/2017.
//

RRQpacket::RRQpacket(std::string fileName) {
    fileName_ = fileName;
}

std::string RRQpacket::getFileName() {
    return fileName_;
}
