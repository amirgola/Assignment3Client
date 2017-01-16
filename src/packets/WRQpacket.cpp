#include "./../include/WRQpacket.h"

//
// Created by Medhopz on 1/16/2017.
//

WRQpacket::WRQpacket(string fileName) {
    fileName_ = fileName;
}

string WRQpacket::getFileName() {
    return fileName_;
}
