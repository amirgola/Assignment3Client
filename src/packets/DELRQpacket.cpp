#include "./../include/DELRQpacket.h"

//
// Created by Medhopz on 1/16/2017.
//

DELRQpacket::DELRQpacket(string fileName) {
    fileName_ = fileName;
}

string DELRQpacket::getFileName() {
    return fileName_;
}
