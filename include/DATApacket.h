#ifndef DATAPACKET_H_
#define DATAPACKET_H_

class DATApacket : public Packet{
private:
    short packetSize_;
    short blockNumber_;
    vector<char> data_;
public:
    DATApacket(short packetSize, short blockNumber, vector<char> data);
    vector<char> getData();
    short getBlockNumber();
    short getPacketSize();
};