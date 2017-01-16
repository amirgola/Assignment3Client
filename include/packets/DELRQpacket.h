#ifndef DELRQPACKET_H_
#define DELRQPACKET_H_

#include "Packet.h"

class DELRQpacket : public Packet{
private:
    std::string fileName_;
public:
    DELRQpacket(std::string fileName);
    std::string getFileName();
};

#endif