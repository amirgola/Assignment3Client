#ifndef ERRORPACKET_H_
#define ERRORPACKET_H_

#include "Packet.h"

class ERRORpacket : public Packet{
private:
    short errCode;
    std::string errMsg;
public:
    ERRORpacket(short errCode, std::string errMsg);
    short getErrCode();
    std::string getErrMsg();
};

#endif