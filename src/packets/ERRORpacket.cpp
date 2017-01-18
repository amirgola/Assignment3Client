#include "./../../include/packets/ERRORpacket.h"
#include "./../../include/packets/Packet.h"
//
// Created by Medhopz on 1/16/2017.
//

ERRORpacket::ERRORpacket(short errCode, std::string errMsg):Packet::Packet(5) {
    errCode = errCode;
    errMsg = errMsg;
}

short ERRORpacket::getErrCode() {
    return errCode;
}

std::string ERRORpacket::getErrMsg() {
    return errMsg;
}
