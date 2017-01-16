#include "./../include/BCASTpacket.h"

//
// Created by Medhopz on 1/16/2017.
//

BCASTpacket::BCASTpacket(char delAdd, string fileName) {
    fileName_ = fileName;
    delAdd_ = delAdd;
}

string BCASTpacket::getFileName() {
    return fileName_;
}

char BCASTpacket::getDelAdd() {
    return delAdd_;
}
