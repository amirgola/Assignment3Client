#ifndef BCASTPACKET_H_
#define BCASTPACKET_H_

#include "Packet.h"

class BCASTpacket : public Packet{
private:
    std::string filename_;
    char delAdd_;
public:
    BCASTpacket(char delAdd, string fileName);
    std::string getFilname();
    char getDelAdd();
};

#endif