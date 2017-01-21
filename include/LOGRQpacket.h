#ifndef LOGRQPACKET_H_
#define LOGRQPACKET_H_

#include "Packet.h"

class LOGRQpacket : public Packet{
private:
    std::string userName_;
public:
    LOGRQpacket(std::string userName);
    std::string getUserName();
};

#endif