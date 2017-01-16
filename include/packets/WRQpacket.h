#ifndef WRQPACKET_H_
#define WRQPACKET_H_

#include "Packet.h"

class WRQpacket : public Packet{
private:
    std::string fileName_;
public:
    WRQpacket(std::string fileName);
    std::string getFileName();
};

#endif