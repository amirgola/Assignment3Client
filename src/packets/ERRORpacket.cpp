#include "./../include/ERRORpacket.h"

//
// Created by Medhopz on 1/16/2017.
//

ERRORpacket::ERRORpacket(short errCode, string errMsg) {
    errCode = errCode;
    errMsg = errMsg;
}

short ERRORpacket::getErrCode() {
    return errCode;
}

string ERRORpacket::getErrMsg() {
    return errMsg;
}
