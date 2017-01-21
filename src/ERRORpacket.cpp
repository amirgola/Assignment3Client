#include "../include/ERRORpacket.h"
#include "../include/Packet.h"
//
// Created by Medhopz on 1/16/2017.
//

ERRORpacket::ERRORpacket(short errCode, std::string errMsg):Packet::Packet(5),_errCode(errCode), _errMsg(errMsg) {
}

short ERRORpacket::getErrCode() {
    return _errCode;
}

std::string ERRORpacket::getErrMsg() {
    return _errMsg;
}
