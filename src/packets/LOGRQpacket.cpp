#include "./../include/LOGRQpacket.h"

//
// Created by Medhopz on 1/16/2017.
//

LOGRQpacket::LOGRQpacket(string userName) {
    userName_ = userName;
}

string LOGRQpacket::getUserName() {
    return userName_;
}
