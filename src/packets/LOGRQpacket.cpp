#include "./../../include/packets/LOGRQpacket.h"

//
// Created by Medhopz on 1/16/2017.
//

LOGRQpacket::LOGRQpacket(std::string userName) {
    userName_ = userName;
}

std::string LOGRQpacket::getUserName() {
    return userName_;
}
