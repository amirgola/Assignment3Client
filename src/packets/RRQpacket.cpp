#include "./../include/RRQpacket.h"

//
// Created by Medhopz on 1/16/2017.
//

RRQpacket::RRQpacket(string fileName) {
    fileName_ = fileName;
}

string RRQpacket::getFileName() {
    return fileName_;
}
