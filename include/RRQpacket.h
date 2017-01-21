#ifndef RRQPACKET_H_
#define RRQPACKET_H_

#include "Packet.h"

class RRQpacket : public Packet{
private:
    std::string fileName_;
public:
    RRQpacket(std::string fileName);
    std::string getFileName();
};

#endif