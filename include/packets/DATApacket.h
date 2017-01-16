#ifndef DATAPACKET_H_
#define DATAPACKET_H_

#include <vector>
#include "Packet.h"

class DATApacket : public Packet{
private:
    short packetSize_;
    short blockNumber_;
    std::vector<char> data_;
public:
    DATApacket(short packetSize, short blockNumber, std::vector<char> data);
    std::vector<char> getData();
    short getBlockNumber();
    short getPacketSize();
};

#endif