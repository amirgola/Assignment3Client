#include "./../../include/packets/WRQpacket.h"

//
// Created by Medhopz on 1/16/2017.
//

WRQpacket::WRQpacket(std::string fileName) {
    fileName_ = fileName;
}

std::string WRQpacket::getFileName() {
    return fileName_;
}
