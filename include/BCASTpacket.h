#ifndef BCASTPACKET_H_
#define BCASTPACKET_H_

#include "Packet.h"

class BCASTpacket : public Packet{
private:
    std::string filename_;
    char delAdd_;
public:
    BCASTpacket(char delAdd, std::string fileName);
    std::string getFileName();
    char getDelAdd();
};

#endif