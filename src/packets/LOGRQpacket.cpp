#include "./../../include/packets/LOGRQpacket.h"
#include "./../../include/packets/Packet.h"
//
// Created by Medhopz on 1/16/2017.
//

LOGRQpacket::LOGRQpacket(std::string userName):Packet::Packet(7) {
    userName_ = userName;
}

std::string LOGRQpacket::getUserName() {
    return userName_;
}
