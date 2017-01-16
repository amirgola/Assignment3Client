#include "./../../include/packets/DELRQpacket.h"

//
// Created by Medhopz on 1/16/2017.
//

DELRQpacket::DELRQpacket(std::string fileName) {
    fileName_ = fileName;
}

std::string DELRQpacket::getFileName() {
    return fileName_;
}
